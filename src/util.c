#include <string.h>
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
