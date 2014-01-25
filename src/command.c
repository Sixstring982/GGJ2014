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

void Command_Execute(Command* command)
{
  
}
