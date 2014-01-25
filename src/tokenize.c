#include <string.h>
#include <stddef.h>
#include <stdio.h>

#include "tokenize.h"
#include "command.h"

#define MAX_LIST_SIZE 64

char ** tokenize(const char string[])
{
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

  return tokenv;
}
