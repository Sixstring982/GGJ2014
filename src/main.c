#define RUN_TESTS 0
#if RUN_TESTS
#include "tests.h"
#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "itype.h"
#include "console.h"
#include "tokenize.h"
#include "departments.h"
#include "gamestate.h"

u32 args[] = {1234};

void PauseDelay(GameState* state, u32 ticks)
{
  CommandFunc cfunc;
  Command* cmd;
  cfunc.c1 = &GameState_Pause;
  cmd = MallocCommand(state->currentTick + ticks, args, 1, cfunc);
  GameState_InsertCommand(state, cmd);
}

void RunSub()
{ 
  char buffer[MAX_BUFFER_LENGTH];
  bool running = true;
  GameState state;
  
  GameState_Init(&state);
    
  while(running)
  {
    GameState_Tick(&state);
    printf("Tick[%d]\n", state.currentTick);
    if(Console_DataAvailable())
    {
      Console_ReadLine(buffer);
      printf("[%s]\n", buffer);
      if(!strcmp(buffer, "quit"))
      {
	running = false;
      }
      else if(!strcmp(buffer, "pause"))
      {
	PauseDelay(&state, 3);
      }
    }
  }
}

int main(int argc, char** argv)
{
  RunSub();
  return 0;
}

#endif /*RUN_TESTS*/
