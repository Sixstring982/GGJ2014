#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "tokenparse.h"
#include "command.h"

#define MAX_LIST_SIZE 64

Command * tokenparse(const char string[])
{
    int delay = 0;
    char cmp[] = "delay";
    int i;


  const char delimiters[] = " \t.,;:!-";
  char running[MAX_LIST_SIZE];
  u32 numtokens = 0;

  char **tmp, *tokenv[MAX_LIST_SIZE];

  strcpy(running, string);

  for (tmp = tokenv; (*tmp = strtok(running, delimiters)) != NULL; numtokens++)
  {
    if (**tmp != '\0')
    {
      if (++tmp >= &tokenv[MAX_LIST_SIZE])
      {
	break;
      }
    }
  }


    /* look for delay syntax */
    for(i = 0; i < numtokens; i++)
    {
      if(!strcmp(tokenv[i],cmp))
        delay = atoi(tokenv[++i]);
    }

  return NULL;
}
