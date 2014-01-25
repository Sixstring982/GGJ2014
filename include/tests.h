#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "pque.h"

void TestPQue()
{
  PQue queue;
  u32 i;
  u32 highest = 0;
  PQue_Init(&queue);

  for(i = 0; i < 32; i++)
  {
    CommandFunc f;
    Command* cmd = MallocCommand(rand(), NULL, 0, f);
    PQue_Insert(&queue, cmd);
  }

  
  for(i = 0; i < 32; i++)
  {
    Command* cmd = PQue_Remove(&queue);

    if(cmd->executionTick <= highest)
    {
      perror("TestPque FAILED!");
      exit(1);
    }
    highest = cmd->executionTick;

    FreeCommand(cmd);
  }
}

int main(int argc, char** argv)
{
  TestPQue();
  return 0;
}
