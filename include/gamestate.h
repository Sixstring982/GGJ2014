#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "itype.h"
#include "pque.h"

typedef struct s_gameState
{
  bool paused;
  u32 currentTick;
  PQue eventQueue;
}GameState;

extern void GameState_Init(GameState* state);

extern void GameState_Tick(GameState* state);

extern void GameState_Pause(GameState* state);

extern void GameState_InsertCommand(GameState* state, Command* command);

#endif /*GAMESTATE_H*/
