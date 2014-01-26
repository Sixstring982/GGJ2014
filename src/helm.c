#include <stdio.h>
#include "helm.h"
#include "util.h"

#define COLOR_CYAN    "\033[36m"      /* Cyan */
#define COLOR_RESET   "\033[0m"


void Rotate(GameState* state, u32 targetHeading, bool counterClockwise)
{
  if(counterClockwise)
  {
    state->heading -= HELM_ROTATION_DEGREES_PER_TICK;
  }
  else
  {
    state->heading += HELM_ROTATION_DEGREES_PER_TICK;
  }

  if(state->heading < 0)
  {
    state->heading += 360;
  }
  if(state->heading > 360)
  {
    state->heading -= 360;
  }

  if(ABS(state->heading - targetHeading) >= HELM_ROTATION_DEGREES_PER_TICK)
  {
    CommandFunc func;
    Command* cmd;
    u32 args[1];
    args[0] = targetHeading;
    
    if(counterClockwise)
    {
      func.c1 = &Helm_RotateCounterClockwise;
    }
    else
    {
      func.c1 = &Helm_RotateClockwise;
    }
    cmd = MallocCommand(state->currentTick + 1, args, 1, func);
    GameState_InsertCommand(state, cmd);

    printf(COLOR_CYAN "[HELM] At %d degrees. Rotating towards %d degrees." COLOR_RESET "\n", state->heading, targetHeading);
  }
  else
  {
    printf(COLOR_CYAN "[HELM] Heading %d Reached. " COLOR_RESET "\n", state->heading);
  }
}

void Helm_RotateCounterClockwise(GameState* state, u32 targetHeading)
{
  Rotate(state, targetHeading, true);
}

void Helm_RotateClockwise(GameState* state, u32 targetHeading)
{
  Rotate(state, targetHeading, false);
}

void Helm_ListHeading(GameState* state)
{
  printf(COLOR_CYAN "[HELM] Current heading: %d degrees." COLOR_RESET "\n", state->heading);
}
