#include <stdio.h>
#include <stdlib.h>
#include "gamestate.h"
#include "util.h"

#define COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define TEXT_RESET   "\033[0m"
#define COLOR_RESET   "\033[0m"

#define COLOR_BLUE    "\033[34m"      /* Blue */


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
      if(e->heading == t->heading ||
	 (t->booster && (ABS(t->heading - e->heading) < ENEMY_DIFFUSE_LATERAL)))
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

void GameState_UpdateEnemies(GameState* state)
{
  u32 i;
  for(i = 0; i < ENEMY_ARRAY_LENGTH; i++)
  {
    if(state->enemies[i].alive)
    {
      Enemy_Update(state->enemies + i);
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
