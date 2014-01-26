#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "sonar.h"
#include "tokenparse.h"
#include "command.h"

#define MAX_LIST_SIZE 64

Command* parseHelmToken(char** tokens, u32 currentTick)
{
  return NULL;
}

Command* parseSonarToken(char** tokens, u32 currentTick)
{
  if(!strcmp("list", tokens[0]) &&
     !strcmp("contacts", tokens[1]))
  {
    CommandFunc cfunc;

    cfunc.c0 = &Sonar_PrintContacts;
    return MallocCommand(currentTick + 2, NULL, 0, cfunc);
  }
  
  return NULL;
}

  Command* parseFirstToken(char** tokens, u32 currentTick)
{
  if(!strcmp("helm", tokens[0]))
  {
    return parseHelmToken(tokens + 1, currentTick);
  }
  else if(!strcmp("sonar", tokens[0]))
  {
    return parseSonarToken(tokens + 1, currentTick);
  }

  return NULL;
}

Command* tokenparse(const char str[], u32 currentTick)
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

  tokens = (char**)malloc(sizeof(char*) * (delimCt + 2));
  for(i = 0; i < delimCt + 1; i++)
  {
    tokens[i] = (char*)malloc(sizeof(char) * MAX_LIST_SIZE);
  }
  tokens[i] = NULL;
  
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

  return parseFirstToken(tokens, currentTick + delay); 
}
