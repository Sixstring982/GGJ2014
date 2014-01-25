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

void RunSub()
{ 
  char buffer[MAX_BUFFER_LENGTH];
  bool running = true;
  GameState state;
  
  GameState_Init(&state);
    
  while(running)
  {
    GameState_Tick(&state);

    if(Console_DataAvailable())
    {
      Console_ReadLine(buffer);
      if(!strcmp(buffer, "quit"))
      {
	running = false;
      }
      else if(!strcmp(buffer, "pause"))
      {
	GameState_Pause(&state);
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
