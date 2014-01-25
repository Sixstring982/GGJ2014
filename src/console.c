#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include "console.h"

bool Console_DataAvailable()
{
  fd_set rfds;
  struct timeval tv;
  int retval;

  FD_ZERO(&rfds);
  FD_SET(0, &rfds);

  tv.tv_sec = TICK_SECS;
  tv.tv_usec = 0;

  retval = select(1, &rfds, NULL, NULL, &tv);

  switch(retval)
  {
<<<<<<< HEAD
  case -1: perror("IOError in select!\n"); exit(5);
    return false;
=======
  case -1: perror("IOError in select!\n"); exit(5); return false;
>>>>>>> 4209d7fa695ed3ca80122e5b0635d01b657a6f19
  case 0:  return false;
  default:  return true;
  }
  
}

void Console_ReadLine(char* toBuffer)
{
  int readC;
  s32 i;
  for(i = 0; i < MAX_BUFFER_LENGTH; i++)
  {
    switch((readC = fgetc(stdin)))
    {
    case '\n': toBuffer[i] = 0; return;
    default: toBuffer[i] = readC; break;
    }
  }
}
