#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "enemy.h"
#include "itype.h"
#include "pque.h"
#include "torpedo.h"

#define TORPEDO_ARRAY_LENGTH 0xff
#define ENEMY_ARRAY_LENGTH 0xff
#define GAMESTATE_INITIAL_ENEMIES 3
#define GAMESTATE_INITIAL_HEALTH 100
#define GAMESTATE_TORPEDO_DAMAGE 30
#define ENEMY_SPAWN_ODDS 300

typedef struct s_gameState
{
  bool paused;
  u32 currentTick;
  s32 heading;
  u32 ammunition;
  u32 currentTorpedo;
  s32 currentHealth;
  PQue eventQueue;
  Torpedo torpedos[TORPEDO_ARRAY_LENGTH];
  Enemy enemies[ENEMY_ARRAY_LENGTH];
}GameState;

extern void GameState_GetAmmoCount(u32 ammoType);

extern void GameState_AddAmmoCount(u32 ammoType, s32 offset);

extern void GameState_Init(GameState* state);

extern void GameState_InitPreserveTime(GameState* state);

extern void GameState_Tick(GameState* state);

extern void GameState_Pause(GameState* state);

extern void GameState_InsertCommand(GameState* state, Command* command);

extern void GameState_SpawnEnemy(GameState* state);

#endif /*GAMESTATE_H*/
