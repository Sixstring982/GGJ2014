#include <stdio.h>
#include "torpedo.h"

void Torpedo_Init(Torpedo* t)
{
  t->booster = t->warhead = t->homing = false;
  t->state = TORPEDOSTATE_STORAGE;
  t->distance = 0;
}

void Torpedo_Advance(Torpedo* t)
{
  u32 speed = t->booster ? TORPEDO_BOOST_SPEED : TORPEDO_NORMAL_SPEED;

  t->distance += speed;

  if(t->distance > TORPEDO_MAX_DISTANCE)
  {
    t->state = TORPEDOSTATE_STORAGE;
    printf("[WEAPONS]: Torpedo missed.\n");
  }
}

void Torpedo_SetState(Torpedo* t, TorpedoState state)
{
  t->state = state;
}
