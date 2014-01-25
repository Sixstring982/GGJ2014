#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "itype.h"
#include "console.h"

int main(int argc, char** argv)
{
  char buffer[MAX_BUFFER_LENGTH];
  bool running = true;
  
  while(running)
  {
    printf("Tick!\n");
    if(Console_DataAvailable())
    {
      Console_ReadLine(buffer);
      printf("[%s]\n", buffer);
      if(!strcmp(buffer, "quit"))
      {
	running = false;
      }
    }
  }
}
