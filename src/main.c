#define RUN_TESTS 0
#if RUN_TESTS
#include "tests.h"
#else


#define COLOR_RESET   "\033[0m"
#define COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define COLOR_BLUE    "\033[34m"      /* Blue */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "itype.h"
#include "console.h"
#include "tokenparse.h"
#include "departments.h"
#include "gamestate.h"

void PrintManual()
{
  printf(COLOR_BOLDBLUE);
  printf("%-12s%-25s%-25s%-25s\n", "department", "example command", "notes", "base delay");
  printf(COLOR_BOLDBLACK);

  printf("\n%-12s%-25s%-25s%-25s\n",  "helm", "rotate ",              "rotates ship to heading",    "1 tick per 15 degrees");
  printf("%-12s%-25s%-25s%-25s\n",    "",     "counterclockwise 30",  "of 30 degrees in the",        "");
  printf("%-12s%-25s%-25s%-25s\n",    "",     "",                     "counterclockwise ",  "");
  printf("%-12s%-25s%-25s%-25s\n",    "",     "",                     "direction",          "");

  printf("\n%-12s%-25s%-25s%-25s\n",  "",     "list heading", "displays heading","1 tick");

  printf("\n%-12s%-25s%-25s%-25s\n", "sonar", "list contacts", "lists enemies", "1 tick ");

  printf("\n%-12s%-25s%-25s%-25s\n", "weapons", "prep", "preps a torpedo", "2 ticks");

  printf("\n%-12s%-25s%-25s%-25s\n", "",         "upgrade booster/", "upgrades torpedo", "5 ticks per upgrade");
  printf("%-12s%-25s%-25s%-25s\n", "",           "warhead/homing", "", "");

  printf("\n%-12s%-25s%-25s%-25s\n", "",         "load", "loads torpedo", "2 ticks");

  printf("\n%-12s%-25s%-25s%-25s\n", "",          "fire", "fires torpedo", "1 tick per 20 meters");
  printf(COLOR_RESET);

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

    if(Console_DataAvailable())
    {
      Command* cmd = NULL;
      Console_ReadLine(buffer);
      if(!strcmp(buffer, "quit"))
      {
	running = false;
      }
      else if(!strcmp(buffer,"manual") || !strcmp(buffer,"help"))
          PrintManual();
      else if(!strcmp(buffer, "pause"))
      {
	GameState_Pause(&state);
      }
      else if((cmd = tokenparse(buffer, state.currentTick)))
      {
	GameState_InsertCommand(&state, cmd);
      }
      else if(!strcmp(buffer, ""))
      {
	printf("Unrecognized command.\n");
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
