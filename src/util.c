#include <string.h>
#include <stdlib.h>
#include "itype.h"

bool IsDigits(char* str)
{
  u32 len = strlen(str), i, j;
  const char digits[] = "0123456789";

  bool digit;
  for(i = 0; i < len; i++)
  {
    digit = false;
    for(j = 0; j < 10; j++)
    {
      if(str[i] == digits[j])
      {
	digit = true;
      }
    }
    if(!digit)
    {
      return false;
    }
  }
  return true;
}

static const u32 BINOMIAL_BINS[] =
  {1, 8, 28, 56, 70, 56, 28, 8, 1};
static const u32 BINOMIAL_TOTAL = 256;
u32 BinomialDistribution(u32 min, u32 max)
{
  u32 binSize = (max - min) / 9;

  u32 binPick = rand() % BINOMIAL_TOTAL;

  u32 i, acc = 0;
  
  for(i = 0; i < 9; i++)
  {
    acc += BINOMIAL_BINS[i];
    if(binPick < acc)
    {
      break;
    }
  }

  return (rand() % binSize) + (i * binSize) + min;
}
