#include <stdio.h>
#include "weapons.h"

/* Returns the index of the first 'type'd torpedo, or -1 if there isn't one. */
s32 FirstTorpedoOfType(GameState* state, TorpedoState type)
{
  u32 i;
  for(i = 0; i < TORPEDO_ARRAY_LENGTH; i++)
  {
    if(state->torpedos[i]->state == type)
    {
      return i;
    }
  }
  return -1; 
}

/* Returns the index of the loaded torpedo, or -1 if there isn't one. */
s32 TorpedoLoaded(GameState* state)
{
  return FirstTorpedoOfType(state, TORPEDOSTATE_LOAD);
}

/* Returns the index of the prepped torpedo, or -1 if there isn't one. */
s32 TorpedoPrepped(GameState* state)
{
  return FirstTorpedoOfType(state, TORPEDOSTATE_PREP);
}

s32 TorpedoStorage(GameState* state)
{
  return FirstTorpedoOfType(state, TORPEDOSTATE_STORAGE);
}

void PrepTorpedo(GameState* state)
{
  if(TorpedoPrepped(state) != -1)
  {
    printf("[WEAPONS]: Prep torpedo failed; Torpedo already being prepped.\n");
  }
  else
  {
    s32 storeIdx = TorpedoStorage(state);
    if(storeIdx == -1)
    {
      printf("[WEAPONS]: Prep torpedo failed; No torpedos in storage.\n");
    }
  }
}

void Weapons_LoadTorpedo(GameState* state)
{
  if(TorpedoLoaded(state) != -1)
  {
    printf("[WEAPONS]: Load torpedo failed; Torpedo already loaded.\n");
  }
  else
  {
    s32 prepped = TorpedoPrepped(state);
    if(prepped == -1)
    {
      printf("[WEAPONS]: Load torpedo failed; No prepped torpedo. use {torpedo prep} first.\n");
    }
    else
    {
      Torpedo* t = state->torpedos[prepped];
      printf("[WEAPONS]: %s%s%s torpedo loaded.\n", 
	     t->booster ? "booster " : "",
	     t->warhead ? "warhead " : "",
	     t->homing  ? "homing "  : "");
      Torpedo_SetState(t, TORPEDOSTATE_LOAD);
    }
  }
}
