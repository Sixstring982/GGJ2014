#include <stdio.h>
#include <stdlib.h>
#include "enemy.h"
#include "util.h"

#define COLOR_MAGENTA "\033[35m"      /* Magenta */
#define COLOR_RESET   "\033[0m"

void Enemy_Init(Enemy* e)
{
  e->heading = e->distance = 0;
  e->alive = false;
  Torpedo_Init(&e->torpedo);
}

void Enemy_Spawn(Enemy* e)
{
  e->heading = (rand() % 24) * 15;
  e->distance = (rand() % 50) * 20;
  e->alive = true;
  Torpedo_Init(&e->torpedo);

  printf(COLOR_MAGENTA "[SONAR]: Enemy contact has been spotted." COLOR_RESET "\n");
}

