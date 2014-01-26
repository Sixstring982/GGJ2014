#ifndef WEAPONS_H
#define WEAPONS_H

#include "itype.h"
#include "gamestate.h"
#include "torpedo.h"

void Weapons_LoadTorpedo(GameState* state);

void Weapons_FireTorpedo(GameState* state);

void Weapons_PrepTorpedo(GameState* state);

void Weapons_Upgrade(GameState* state, u32 upgradeIdx);

void Weapons_ListStatus(GameState* state);

void Weapons_ChangeTorpedoType(GameState* state, TorpedoState type);

void Weapons_ChangeTorpedoType(GameState* state, TorpedoState type);

void AddToBoosters(GameState* state, u32 amt);

void AddToWarheads(GameState* state, u32 amt);

void AddToHomings(GameState* state, u32 amt);

#endif /*WEAPONS_H*/
