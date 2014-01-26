#include <stdio.h>
#include <stdlib.h>
#include "gamestate.h"
#include "util.h"

#define COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define COLOR_BLUE    "\033[34m"      /* Blue */
#define COLOR_RED     "\033[31m"      /* Red */
#define TEXT_RESET   "\033[0m"
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


#define TEXT_BLINK    "\033[5m"      /* BLINK */
#define TEXT_BLINKOFF   "\033[25m"      /* NO BLINK */

#define COLOR_BACK_RED     "\033[41m"      /* Red background */
#define COLOR_BACK_RED_HIGH     "\033[101m"      /* Red background high intensity */

#define COLOR_BACK_RESET    "\033[40m"      /* reset background */

void GameState_Init(GameState* state)
{
  u32 i;
  state->currentTick = 0;
  state->paused = false;
  state->heading = 15 * (rand() % 24);
  state->ammunition = 0xffffff;
  state->currentHealth = GAMESTATE_INITIAL_HEALTH;
  PQue_Init(&(state->eventQueue));

  state->currentTorpedo = 0;
  for(i = 0; i < TORPEDO_ARRAY_LENGTH; i++)
  {
    Torpedo_Init(state->torpedos + i);
  }

  for(i = 0; i < ENEMY_ARRAY_LENGTH; i++)
  {
    Enemy_Init(state->enemies + i);
  }

  for(i = 0; i < GAMESTATE_INITIAL_ENEMIES; i++)
  {
    GameState_SpawnEnemy(state);
  }
}

void GameState_Pause(GameState* state)
{
  state->paused = !state->paused;
  printf("Game %s.\n", state->paused ? "paused" : "unpaused");
}

void Command_Execute(Command* command, GameState* state)
{
  u32* a = command->commandArgs;
  switch(command->argLength)
  {
  case 0: command->commFunc.c0(state); break;
  case 1: command->commFunc.c1(state, a[0]); break;
  case 2: command->commFunc.c2(state, a[0], a[1]); break;
  case 3: command->commFunc.c3(state, a[0], a[1], a[2]); break;
  case 4: command->commFunc.c4(state, a[0], a[1], a[2], a[3]); break;
  default: perror("Command_Execute: Invalid argument length!"); 
  exit(3); 
  return;
  }
}

void EvalCurrentEvents(GameState* state)
{
  Command* cmd;
  while(PQue_Size(&state->eventQueue) > 0 &&
	PQue_Peek(&state->eventQueue)->executionTick <= state->currentTick)
  {
    cmd = PQue_Remove(&state->eventQueue);
    Command_Execute(cmd, state);
    FreeCommand(cmd);
  }
}

void Torpedo_Advance(GameState* state, Torpedo* t)
{
  u32 speed = t->booster ? TORPEDO_BOOST_SPEED : TORPEDO_NORMAL_SPEED;
  u32 i;
  t->distance += speed;

  if(t->distance > TORPEDO_MAX_DISTANCE)
  {
    t->state = TORPEDOSTATE_STORAGE;
    printf("[WEAPONS]: Torpedo missed.\n");
  }

  for(i = 0; i < ENEMY_ARRAY_LENGTH; i++)
  {
    Enemy* e = state->enemies + i;
    if(e->alive)
    {

      Torpedo* et = &e->torpedo;
      if(et->heading == t->heading ||
	 (t->homing && (ABS(t->heading - et->heading) < ENEMY_DIFFUSE_LATERAL)))
      {
	if(t->distance - speed <= et->distance &&
	   t->distance >= et->distance)
	{
	  /* Hit another torpedo! */
	  printf("[SONAR]: Enemy Torpedo destroyed, heading %d degrees.\n", et->heading);
	  Torpedo_Init(t);
	  Torpedo_Init(et);
	  break;
	}
      }

      if(e->heading == t->heading ||
	 (t->homing && (ABS(t->heading - e->heading) < ENEMY_DIFFUSE_LATERAL)))
      {
	if(t->distance - speed <= e->distance &&
	   t->distance >= e->distance)
	{
	  /* HIT! */
	  printf("[WEAPONS]: Enemy neutralized.\n");
	  Torpedo_Init(t);
	  Enemy_Init(e);
	  break;
	}
      }
    }
  }
}


void GameState_AdvanceTorpedos(GameState* state)
{
  u32 i;
  for(i = 0; i < TORPEDO_ARRAY_LENGTH; i++)
  {
    if(state->torpedos[i].state == TORPEDOSTATE_FIRE)
    {
      Torpedo_Advance(state, state->torpedos + i);
    }
  }
}

void UpdateEnemyTorpedo(GameState* state, Enemy* e)
{
  if(e->torpedo.state == TORPEDOSTATE_FIRE)
  {
    e->torpedo.distance -= TORPEDO_NORMAL_SPEED;
    if(e->torpedo.distance <= 0)
    {
      /*We got hit!*/
      state->currentHealth -= GAMESTATE_TORPEDO_DAMAGE;
      if(state->currentHealth < 0)
      {
	state->currentHealth = 0;
      }
      printf(TEXT_BLINK COLOR_BACK_RED "[SONAR]: WARNING! TORPEDO COLLISION! HULL AT %d PERCENT" TEXT_BLINKOFF COLOR_RESET"\n",
	     state->currentHealth);
      if(state->currentHealth <= 0)
      {
	printf("\n" COLOR_BACK_RED_HIGH COLOR_BOLDWHITE TEXT_BLINK "ABANDON SHIP!\n" COLOR_RESET TEXT_BLINKOFF COLOR_BACK_RESET);
      }
      Torpedo_Init(&e->torpedo);
    }
  }
}

void Diffuse(Enemy* e)
{  
  /* Diffuse laterally */
  if(RANDBOOL)
  {
    e->heading += RANDBOOL ? ENEMY_DIFFUSE_LATERAL : -ENEMY_DIFFUSE_LATERAL;
  }

  if(RANDBOOL)
  {
    e->distance += RANDBOOL ? ENEMY_DIFFUSE_FORWARD : -ENEMY_DIFFUSE_FORWARD;
  }
}

void Fire(Enemy* e)
{
  if(e->torpedo.state != TORPEDOSTATE_FIRE)
  {
    e->torpedo.heading = e->heading;
    e->torpedo.distance = e->distance;
    e->torpedo.state = TORPEDOSTATE_FIRE;
    printf(TEXT_BLINK COLOR_RED "[SONAR]: Enemy torpedo detected; Heading %d degrees." TEXT_BLINKOFF COLOR_RESET "\n", e->torpedo.heading);
  }
}


void Enemy_Update(GameState* state, Enemy* e)
{
  if(RANDONEIN(ENEMY_DIFFUSE_ODDS))
  {
    Diffuse(e);
  }
  if(RANDONEIN(ENEMY_FIRE_ODDS))
  {
    Fire(e);
  }
  UpdateEnemyTorpedo(state, e);
}

void GameState_UpdateEnemies(GameState* state)
{
  u32 i;
  for(i = 0; i < ENEMY_ARRAY_LENGTH; i++)
  {
    if(state->enemies[i].alive)
    {
      Enemy_Update(state, state->enemies + i);
    }
  }
}

void GameState_Tick(GameState* state)
{
  if(!state->paused)
  {
    state->currentTick++;
    EvalCurrentEvents(state);
    GameState_AdvanceTorpedos(state);
    GameState_UpdateEnemies(state);
    printf(COLOR_BOLDBLACK "---- %04d ----" TEXT_RESET "\n", state->currentTick);
  }
}

void GameState_InsertCommand(GameState* state, Command* command)
{
  PQue_Insert(&state->eventQueue, command);
  printf(COLOR_BLUE "[[EXECUTION SCHEDULED: %04d]]" COLOR_RESET "\n", command->executionTick);
}

void GameState_SpawnEnemy(GameState* state)
{
  u32 i;
  for(i = 0; i < ENEMY_ARRAY_LENGTH; i++)
  {
    if(!state->enemies[i].alive)
    {
      Enemy_Spawn(state->enemies + i);
      break;
    }
  }
}
