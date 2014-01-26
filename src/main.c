#define RUN_TESTS 0
#if RUN_TESTS
#include "tests.h"
#else


#define COLOR_RESET   "\033[0m"
#define COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define COLOR_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define COLOR_YELLOW  "\033[33m"      /* Yellow */
#define COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define COLOR_GREEN   "\033[32m"      /* Green */
#define COLOR_MAGENTA "\033[35m"      /* Magenta */
#define COLOR_CYAN    "\033[36m"      /* Cyan */

#define TEXT_BLINK    "\033[5m"      /* BLINK */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "itype.h"
#include "console.h"
#include "tokenparse.h"
#include "departments.h"
#include "gamestate.h"

void PrintManual()
{
  printf(COLOR_YELLOW);
  printf("%-13s%-25s%-25s%-25s\n", "--------------", "-------------------------", "-------------------------", "-------------------------");

  printf("%-13s%-25s%-25s%-25s\n", "[department]", "[example command]", "[notes]", "[base delay]");
  printf("%-13s%-25s%-25s%-25s\n", "--------------", "-------------------------", "-------------------------", "-------------------------");

  printf(COLOR_RESET);

  printf("\n" COLOR_CYAN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n",  "helm", "rotate" ,  "rotates ship to heading",  "1 tick per 15 degrees");
  printf(COLOR_CYAN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n",    "",   "counterclockwise 30", "of 30 degrees in the", "");
  printf(COLOR_CYAN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n",    "",     "",                             "counterclockwise ",  "");
  printf(COLOR_CYAN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n",    "",     "",                             "direction",          "");

  printf(COLOR_CYAN "\n%-13s%-25s" COLOR_RESET "%-25s%-25s\n", "helm", "list heading", "displays heading", "1 tick");

  printf("\n" COLOR_MAGENTA "%-13s%-25s" COLOR_RESET "%-25s%-25s\n",  "sonar", "list contacts", "lists enemies", "1 tick ");

  printf("\n" COLOR_GREEN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n", "weapons", "status", "lists the status of", "1 click");
  printf(COLOR_GREEN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n", "",        "",       "your weapons",  "");

  printf("\n" COLOR_GREEN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n", "weapons", "prep", "preps a torpedo", "2 ticks");

  printf("\n" COLOR_GREEN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n", "weapons", "upgrade booster/", "upgrades a prepped", "5 ticks per upgrade");
  printf(COLOR_GREEN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n",       "",       "warhead/homing",    "torpedo", "");

  printf("\n" COLOR_GREEN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n", "weapons", "load", "loads torpedo", "2 ticks");

  printf("\n" COLOR_GREEN "%-13s%-25s" COLOR_RESET "%-25s%-25s\n", "weapons", "fire", "fires torpedo", "1 tick per 20 meters");
  printf(COLOR_RESET);

}

void RunSub()
{ 
  char buffer[MAX_BUFFER_LENGTH];
  bool running = true;
  GameState state;

  srand(time(NULL));
  
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
      else if(!strcmp(buffer,"manual") || !strcmp(buffer,"help") ||  !strcmp(buffer,"h") )
          PrintManual();
      else if(!strcmp(buffer, "pause"))
      {
	GameState_Pause(&state);
      }
      else if((cmd = tokenparse(buffer, state.currentTick)))
      {
	GameState_InsertCommand(&state, cmd);
      }
      else if(strcmp(buffer, ""))
      {
	printf(COLOR_YELLOW "Unrecognized command." COLOR_YELLOW "\n");
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
