#include <stdio.h>
#include "torpedo.h"

void Torpedo_Init(Torpedo* t)
{
  t->booster = t->warhead = t->homing = false;
  t->state = TORPEDOSTATE_STORAGE;
  t->distance = 0;
}

void Torpedo_SetState(Torpedo* t, TorpedoState state)
{
  t->state = state;
}
