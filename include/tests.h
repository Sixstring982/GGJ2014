#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "command.h"
#include "pque.h"
#include "util.h"

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
      fprintf(stderr, "TestPque FAILED! %d %d", highest, cmd->executionTick);
      exit(1);
    }
    highest = cmd->executionTick;

    FreeCommand(cmd);
  }
}

void TestBinomialDistribution()
{
  u32 i;
  for(i = 0; i < 30; i++)
  {
    printf("[%3d]", 20 * BinomialDistribution(10, 60));

    if(!((i + 1) % 10))
    {
      printf("\n");
    }
  }
}

int main(int argc, char** argv)
{
  srand(time(NULL));
  TestPQue();
  TestBinomialDistribution();
  return 0;
}
