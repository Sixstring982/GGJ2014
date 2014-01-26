#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_DIFFUSE_LATERAL 15
#define ENEMY_DIFFUSE_FORWARD 40

#include "itype.h"

typedef struct s_enemy
{
  u32 heading;
  u32 distance;
}Enemy;

extern void Enemy_Init(Enemy* e);

#endif /*ENEMY_H*/
