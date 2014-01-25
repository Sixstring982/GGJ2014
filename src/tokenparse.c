#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "tokenparse.h"
#include "command.h"

#define MAX_LIST_SIZE 64

Command* tokenparse(const char str[])
{
  const char delimiters[] = " \t.,;:!-";
  int delay;
  char cmdd[] = "delay";

  u32 delimCt = 0, i, j, slen = strlen(str), dlen = strlen(delimiters), currDelim, currChar;
  char** tokens;

  for(i = 0; i < slen; i++)
  {
    for(j = 0; j < dlen; j++)
    {
      if(str[i] == delimiters[j])
      {
	delimCt++;
	break;
      }
    }
  }

  tokens = (char**)malloc(sizeof(char*) * (delimCt + 1));
  for(i = 0; i < delimCt + 1; i++)
  {
    tokens[i] = (char*)malloc(sizeof(char) * MAX_LIST_SIZE);
  }
  
  currChar = currDelim = 0;
  for(i = 0; i < slen; i++)
  {
    bool foundDelim = false;
    for(j = 0; j < dlen; j++)
    {
      if(str[i] == delimiters[j])
      {
	foundDelim = true;
	break;
      }
    }
    
    if(foundDelim)
    {
      currDelim++;
      currChar = 0;
    }
    else
    {
      tokens[currDelim][currChar++] = str[i];
    }
  }

  for (i = 0; i<delimCt + 1; i++)
  {
    if(!strcmp(cmdd, tokens[i]) )
      delay = atoi(tokens[++i]);
  }




  for(i = 0; i < delimCt + 1; i++)
  {
    printf("[%s]", tokens[i]);
  }

  return NULL; 
}
