#include <stdlib.h>
#include "enemy.h"

void Enemy_Init(Enemy* e)
{
  e->heading = (rand() % 24) * 15;
  e->distance = (rand() % 50) * 20;
}
