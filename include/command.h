#ifndef COMMAND_H
#define COMMAND_H

#include "itype.h"

struct s_gameState;

typedef void (*CommFunc0)(struct s_gameState*);
typedef void (*CommFunc1)(struct s_gameState*, u32);
typedef void (*CommFunc2)(struct s_gameState*, u32, u32);
typedef void (*CommFunc3)(struct s_gameState*, u32, u32, u32);
typedef void (*CommFunc4)(struct s_gameState*, u32, u32, u32, u32);

typedef union u_commandFunc
{
  CommFunc0 c0;
  CommFunc1 c1;
  CommFunc2 c2;
  CommFunc3 c3;
  CommFunc4 c4;
}CommandFunc;

typedef struct s_command
{
  u8 argLength;
  u32 executionTick;
  u32 commandArgs[4];
  CommandFunc commFunc;
}Command;

/* Creates a new Command on the heap and returns a pointer to it. */
/* ARGUMENTS:                                                     */
/* executionTick -- The time that this Command will execute       */
/* args -- The arguments given to this Command                    */
/* argLength -- The number of arguments to use for this Command   */
/* func -- The actual function that will call upon execution      */
extern Command* MallocCommand(u32 executionTick, u32* args, u8 argLength, CommandFunc func);

extern void FreeCommand(Command* command);

#endif /*COMMAND_H*/
