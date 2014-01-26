#include <stdio.h>
#include "sonar.h"

#define COLOR_MAGENTA "\033[35m"      /* Magenta */
#define COLOR_RESET   "\033[0m"


void Sonar_PrintContacts(GameState* state)
{
  u32 i;
  printf(COLOR_MAGENTA"[SONAR] Contacts:" COLOR_RESET "\n");

  for(i = 0; i < ENEMY_ARRAY_LENGTH; i++)
  {
    if(state->enemies[i].alive)
    {
      printf(COLOR_MAGENTA "[SONAR] Contact[%d]: %d degrees, %d meters." COLOR_RESET "\n", i, state->enemies[i].heading, 
	     state->enemies[i].distance);
    }
  }
  
  
  printf(COLOR_RESET);
}
