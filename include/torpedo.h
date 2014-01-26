#ifndef TORPEDO_H
#define TORPEDO_H

#include "itype.h"

#define TORPEDO_NORMAL_SPEED 20
#define TORPEDO_BOOST_SPEED  40
#define TORPEDO_MAX_DISTANCE 1000

typedef enum e_torpedoState
{
  TORPEDOSTATE_STORAGE,
  TORPEDOSTATE_PREP,
  TORPEDOSTATE_LOAD,
  TORPEDOSTATE_FIRE
}TorpedoState;

typedef enum e_torpedoUpgrade
{
  TORPEDOUPGRADE_BOOSTER = 0,
  TORPEDOUPGRADE_WARHEAD = 1,
  TORPEDOUPGRADE_HOMING  = 2
}TorpedoUpgrade;

typedef struct s_torpedo
{
  bool booster;
  bool warhead;
  bool homing;
  TorpedoState state;
  u32 heading;
  u32 distance;
}Torpedo;

extern void Torpedo_Init(Torpedo* t);

extern void Torpedo_Advance(Torpedo* t);

extern void Torpedo_SetState(Torpedo* t, TorpedoState state);

#endif /*TORPEDO_H*/
