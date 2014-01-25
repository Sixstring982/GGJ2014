#include <stdio.h>
#include <stdlib.h>
#include "gamestate.h"

void GameState_Init(GameState* state)
{
  state->currentTick = 0;
  state->paused = false;
  PQue_Init(&(state->eventQueue));
}

void GameState_Pause(GameState* state, u32 number)
{
  state->paused = true;
  printf("Game Paused %d.\n", number);
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

void GameState_Tick(GameState* state)
{
  if(!state->paused)
  {
    state->currentTick++;
    EvalCurrentEvents(state);
  }
}

void GameState_InsertCommand(GameState* state, Command* command)
{
  PQue_Insert(&state->eventQueue, command);
}
