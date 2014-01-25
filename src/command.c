#include <stdlib.h>
#include "command.h"

Command* MallocCommand(u32 executionTick, u32* args, u8 argLength, CommandFunc func)
{
  Command* cmd = (Command*)malloc(sizeof(Command));
  u32 i;

  cmd->executionTick = executionTick;
  cmd->argLength = argLength;
  cmd->commFunc = func;

  for(i = 0; i < argLength; i++)
  {
    cmd->commandArgs[i] = args[i];
  }

  return cmd;
}

void FreeCommand(Command* command)
{
  free(command);
}

void Command_Execute(Command* command, GameState* state)
{
  u32* a = command->commandArgs;
  switch(command->argLength)
  {
  case 0: command->commFunc.c0(state); break;
  case 1: command->commFunc.c1(state, a[0]); break;
  case 2: command->commFunc.c2(state, a[0], a[1]); break;
  case 3: command->commFunc.c3(state, a[0], a[1], a[2]); break;
  case 4: command->commFunc.c4(state, a[0], a[1], a[2], a[3]); break;
  default: perror("Command_Execute: Invalid argument length!"); exit(3); return;
  }
}
