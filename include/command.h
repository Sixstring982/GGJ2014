#ifndef COMMAND_H
#define COMMAND_H

#include "itype.h"
#include "gamestate.h"

typedef void (*commFunc0)(GameState*);
typedef void (*commFunc1)(GameState*, u32);
typedef void (*commFunc2)(GameState*, u32, u32);
typedef void (*commFunc3)(GameState*, u32, u32, u32);
typedef void (*commFunc4)(GameState*, u32, u32, u32, u32);

typedef union u_commandFunc
{
  commFunc0 c0;
  commFunc1 c1;
  commFunc2 c2;
  commFunc3 c3;
  commFunc4 c4;
}CommandFunc;

typedef struct s_command
{
  u32 executionTick;
  u32 commandArgs[4];
  CommandFunc commFunc;
}Command;

extern void MallocCommand(u32 executionTick, u32* args, CommandFunc func);

extern void FreeCommand(Command* command);

#endif /*COMMAND_H*/
