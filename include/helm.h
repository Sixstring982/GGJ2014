#ifndef HELM_H
#define HELM_H

#include "itype.h"
#include "gamestate.h"

#define HELM_ROTATION_DEGREES_PER_TICK 15

extern void Helm_RotateCounterClockwise(GameState* state, u32 targetHeading);

extern void Helm_RotateClockwise(GameState* state, u32 targetHeading);

extern void Helm_ListHeading(GameState* state);

#endif /*HELM_H*/
