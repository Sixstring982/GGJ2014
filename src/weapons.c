#include <stdio.h>
#include "weapons.h"

#define COLOR_GREEN   "\033[32m"      /* Green */
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"      /* Red */
#define COLOR_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define COLOR_RED_HIGH     "\033[91m"      /* Red background */


/* Returns the index of the first 'type'd torpedo, or -1 if there isn't one. */
s32 FirstTorpedoOfType(GameState* state, TorpedoState type)
{
  u32 i;
  for(i = 0; i < TORPEDO_ARRAY_LENGTH; i++)
  {
    if(state->torpedos[i].state == type)
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

u32 BoostersLeft(GameState* state)
{
  return state->ammunition & 0xff;
}

void DecrementBoosters(GameState* state)
{
  u32 boosters = BoostersLeft(state);
  if(boosters > 0)
  {
    boosters--;
    state->ammunition &= 0xffffff00;
    state->ammunition |= boosters;
  }
}

u32 WarheadsLeft(GameState* state)
{
  return (state->ammunition >> 8) & 0xff;
}

void DecrementWarheads(GameState* state)
{
  u32 warheads = WarheadsLeft(state);
  if(warheads > 0)
  {
    warheads--;
    warheads <<= 8;
    state->ammunition &= 0xffff00ff;
    state->ammunition |= warheads;
  }
}

u32 HomingsLeft(GameState* state)
{
  return (state->ammunition >> 16) & 0xff;
}

void DecrementHomings(GameState* state)
{
  u32 homings = WarheadsLeft(state);
  if(homings > 0)
  {
    homings--;
    homings <<= 16;
    state->ammunition &= 0xff00ffff;
    state->ammunition |= homings;
  }
}

s32 TorpedoStorage(GameState* state)
{
  return FirstTorpedoOfType(state, TORPEDOSTATE_STORAGE);
}

void Weapons_PrepTorpedo(GameState* state)
{
  if(TorpedoPrepped(state) != -1)
  {
    printf(COLOR_GREEN "[WEAPONS]: Prep torpedo failed; Torpedo already being prepped." COLOR_RESET"\n");
  }
  else
  {
    s32 storeIdx = TorpedoStorage(state);
    if(storeIdx == -1)
    {
      printf(COLOR_GREEN "[WEAPONS]: Prep torpedo failed; No torpedos in storage." COLOR_RESET "\n");
    }
    else
    {
      printf(COLOR_GREEN "[WEAPONS]: Torpedo prepped. Ready for upgrading or loading." COLOR_RESET "\n");
      Torpedo_SetState(state->torpedos + storeIdx, TORPEDOSTATE_PREP);
    }
  }
}

void Weapons_FireTorpedo(GameState* state)
{
  s32 loaded = TorpedoLoaded(state);
  if(loaded == -1)
  {
    printf(COLOR_GREEN "[WEAPONS]: Torpedo fire failed; No torpedo loaded." COLOR_RESET "\n");
  }
  else
  {
    printf(COLOR_GREEN "[WEAPONS]: Torpedo fired!\n");
    Torpedo_SetState(state->torpedos + loaded, TORPEDOSTATE_FIRE);
    state->torpedos[loaded].heading = state->heading;
  }
}

void Weapons_LoadTorpedo(GameState* state)
{
  if(TorpedoLoaded(state) != -1)
  {
    printf(COLOR_GREEN "[WEAPONS]: Load torpedo failed; Torpedo already loaded." COLOR_RESET "\n");
  }
  else
  {
    s32 prepped = TorpedoPrepped(state);
    if(prepped == -1)
    {
      printf(COLOR_GREEN "[WEAPONS]: Load torpedo failed; No prepped torpedo. use {torpedo prep} first." COLOR_RESET "\n");
    }
    else
    {
      Torpedo* t = state->torpedos + prepped;
      printf(COLOR_GREEN "[WEAPONS]: Torpedo%s%s%s loaded." COLOR_RESET "\n", 
	     t->booster ? " (booster)" : "",
	     t->warhead ? " (warhead)" : "",
	     t->homing  ? " (homing)"  : "");
      Torpedo_SetState(t, TORPEDOSTATE_LOAD);
    }
  }
}

void Weapons_Upgrade(GameState* state, u32 upgradeIdx)
{
  s32 prepped = TorpedoPrepped(state);

  if(prepped == -1)
  {
    printf(COLOR_GREEN "[WEAPONS]: Torpedo upgrade failed; No prepped torpedo. Use {torpedo prep}.\n"
	   COLOR_RESET);
  }
  else
  {
    switch(upgradeIdx)
    {
    case (u32)TORPEDOUPGRADE_BOOSTER:
      if(state->torpedos[prepped].booster)
      {
	printf(COLOR_GREEN "[WEAPONS]: Torpedo upgrade failed; booster already installed.\n"
	       COLOR_RESET);	
      }
      else if(!BoostersLeft(state))
      {
	printf(COLOR_GREEN "[WEAPONS]: Torpedo upgrade failed; no boosters left.\n"
	       COLOR_RESET);	
      }
      else
      {
	printf(COLOR_GREEN "[WEAPONS]: Torpedo booster upgrade applied.\n" COLOR_RESET);
	state->torpedos[prepped].booster = true;
	DecrementBoosters(state);
      }
      break;

    case (u32)TORPEDOUPGRADE_WARHEAD:
      if(state->torpedos[prepped].warhead)
      {
	printf(COLOR_GREEN "[WEAPONS]: Torpedo upgrade failed; warhead already installed.\n"
	       COLOR_RESET);	
      }
      else if(!WarheadsLeft(state))
      {
	printf(COLOR_GREEN "[WEAPONS]: Torpedo upgrade failed; no warheads left.\n"
	       COLOR_RESET);	
      }
      else
      {
	printf(COLOR_GREEN "[WEAPONS]: Torpedo warhead upgrade applied.\n" COLOR_RESET);
	state->torpedos[prepped].warhead = true;
	DecrementWarheads(state);
      }
      break;

    case (u32)TORPEDOUPGRADE_HOMING:
      if(state->torpedos[prepped].homing)
      {
	printf(COLOR_GREEN "[WEAPONS]: Torpedo upgrade failed; homing already installed.\n"
	       COLOR_RESET);	
      }
      else if(!HomingsLeft(state))
      {
	printf(COLOR_GREEN "[WEAPONS]: Torpedo upgrade failed; no homing left.\n"
	       COLOR_RESET);	
      }
      else
      {
	printf(COLOR_GREEN "[WEAPONS]: Torpedo homing upgrade applied.\n" COLOR_RESET);
	state->torpedos[prepped].homing = true;
	DecrementHomings(state);
      }
      break;
    }
  }
}

void Weapons_ListStatus(GameState* state)
{
  u32 i; 
  u32 health;

  printf(COLOR_GREEN "[WEAPONS]: Boosters Warheads Homings" COLOR_RESET "\n");
  printf(COLOR_GREEN "           %3d      %3d      %3d" COLOR_RESET "\n\n", BoostersLeft(state),
	 WarheadsLeft(state),
	 HomingsLeft(state));
  
  health = state -> currentHealth;
  printf("Hull Integrity:");

  if(health > 65)
    printf(COLOR_GREEN);
  else if(health > 30)
    printf(COLOR_BOLDYELLOW);
  else
    printf(COLOR_RED_HIGH);
  printf("%d percent." COLOR_RESET "\n", health);

  printf( "Notable Torpedos:" "\n");

  for(i = 0; i < TORPEDO_ARRAY_LENGTH; i++)
  {
    switch(state->torpedos[i].state)
    {
    case TORPEDOSTATE_PREP:
      printf(COLOR_GREEN "Torpedo[%d]:%s%s%s Prepped." COLOR_RESET "\n", i,
	     state->torpedos[i].booster ? COLOR_GREEN "(booster) " COLOR_RESET : "",
	     state->torpedos[i].warhead ? COLOR_GREEN "(warhead) " COLOR_RESET : "",
	     state->torpedos[i].homing ? COLOR_GREEN "(homing) " COLOR_RESET  : ""); break;
    case TORPEDOSTATE_LOAD:
      printf(COLOR_BOLDYELLOW "Torpedo[%d]:%s%s%s Loaded." COLOR_RESET "\n", i,
	     state->torpedos[i].booster ? COLOR_BOLDYELLOW "(booster) " COLOR_RESET : "",
	     state->torpedos[i].warhead ? COLOR_BOLDYELLOW "(warhead) " COLOR_RESET : "",
	     state->torpedos[i].homing ? COLOR_BOLDYELLOW "(homing) " COLOR_RESET : ""); break;
    case TORPEDOSTATE_FIRE:
      printf(COLOR_RED_HIGH "Torpedo[%d]:%s%s%s Fired. %d degrees, %d meters." COLOR_RESET "\n", i,
	     state->torpedos[i].booster ? COLOR_RED "(booster) " COLOR_RESET : "",
	     state->torpedos[i].warhead ? COLOR_RED "(warhead) " COLOR_RESET : "",
	     state->torpedos[i].homing ? COLOR_RED "(homing) " COLOR_RESET  : "",
	     state->torpedos[i].heading,
	     state->torpedos[i].distance); break;
    default: break;
    }
  }
}
