#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_DIFFUSE_LATERAL 15
#define ENEMY_DIFFUSE_FORWARD 40
#define ENEMY_DIFFUSE_ODDS 100
#define ENEMY_FIRE_ODDS 30
#define ENEMY_HIT_ODDS 50

#include "itype.h"
#include "torpedo.h"

typedef struct s_enemy
{
  bool alive;
  u32 heading;
  u32 distance;
  Torpedo torpedo;
}Enemy;

extern void Enemy_Init(Enemy* e);

extern void Enemy_Spawn(Enemy* e);

#endif /*ENEMY_H*/
