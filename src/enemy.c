#include <stdio.h>
#include <stdlib.h>
#include "enemy.h"
#include "util.h"

void Enemy_Init(Enemy* e)
{
  e->heading = e->distance = 0;
  e->alive = false;
}

void Enemy_Spawn(Enemy* e)
{
  e->heading = (rand() % 24) * 15;
  e->distance = (rand() % 50) * 20;
  e->alive = true;

  printf("[SONAR]: Enemy contact has been spotted.\n");
}

void Diffuse(Enemy* e)
{  
  /* Diffuse laterally */
  if(RANDBOOL)
  {
    e->heading += RANDBOOL ? ENEMY_DIFFUSE_LATERAL : -ENEMY_DIFFUSE_LATERAL;
  }

  if(RANDBOOL)
  {
    e->distance += RANDBOOL ? ENEMY_DIFFUSE_FORWARD : -ENEMY_DIFFUSE_FORWARD;
  }
}

void Enemy_Update(Enemy* e)
{
  if(RANDONEIN(ENEMY_DIFFUSE_ODDS))
  {
    Diffuse(e);
  }
}
