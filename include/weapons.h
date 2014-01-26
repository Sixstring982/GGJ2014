#ifndef WEAPONS_H
#define WEAPONS_H

#include "itype.h"
#include "gamestate.h"
#include "torpedo.h"

void Weapons_LoadTorpedo(GameState* state);

void Weapons_FireTorpedo(GameState* state);

void Weapons_ChangeTorpedoType(GameState* state, TorpedoState type);

void Weapons_ListInventory(GameState* state);

#endif /*WEAPONS_H*/
