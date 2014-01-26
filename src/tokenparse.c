#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "helm.h"
#include "sonar.h"
#include "tokenparse.h"
#include "util.h"
#include "weapons.h"

#define MAX_LIST_SIZE 64

Command* parseWeaponsToken(char** tokens, u32 tokenCt, u32 currentTick)
{
  if(tokenCt >= 1 &&
     !strcmp("prep", tokens[0]))
  {
    CommandFunc cfunc;
    cfunc.c0 = &Weapons_PrepTorpedo;

    return MallocCommand(currentTick + 3, NULL, 0, cfunc);
  }
  if(tokenCt >= 1 &&
     !strcmp("load", tokens[0]))
  {
    CommandFunc cfunc;
    cfunc.c0 = &Weapons_LoadTorpedo;
    
    return MallocCommand(currentTick + 3, NULL, 0, cfunc);
  }
  return NULL;
}

Command* parseHelmToken(char** tokens, u32 tokenCt, u32 currentTick)
{
  if(tokenCt >= 2 &&
     !strcmp("list", tokens[0]) &&
     !strcmp("heading", tokens[1]))
  {
      CommandFunc cfunc;
      cfunc.c0 = &Helm_ListHeading;
      
      return MallocCommand(currentTick + 2, NULL, 0, cfunc);
  }

  if(tokenCt >= 2 &&
     !strcmp("rotate", tokens[0]))
  {
    u32 newAngle = 0;
    if(tokenCt >= 2 &&
       !strcmp("counterclockwise", tokens[1]))
    {
      CommandFunc cfunc;
      u32 args[1];
      if(!IsDigits(tokens[2]))
      {
	return NULL;
      }
      newAngle = atoi(tokens[2]);
      args[0] = TRUNCMOD(newAngle, HELM_ROTATION_DEGREES_PER_TICK);
      cfunc.c1 = &Helm_RotateCounterClockwise;
      
      return MallocCommand(currentTick + 2, args, 1, cfunc);
    }
    else if(tokenCt >= 2 &&
       !strcmp("clockwise", tokens[1]))
    {
      CommandFunc cfunc;
      u32 args[1];
      if(!IsDigits(tokens[2]))
      {
	return NULL;
      }
      newAngle = atoi(tokens[2]);
      args[0] = TRUNCMOD(newAngle, HELM_ROTATION_DEGREES_PER_TICK);
      cfunc.c1 = &Helm_RotateClockwise;
      
      return MallocCommand(currentTick + 2, args, 1, cfunc);
    }
    
    else if(tokenCt >= 1 &&
	    IsDigits(tokens[1]))
    {
      CommandFunc cfunc;
      u32 args[1];
      newAngle = atoi(tokens[1]);
      args[0] = TRUNCMOD(newAngle, HELM_ROTATION_DEGREES_PER_TICK);
      cfunc.c1 = &Helm_RotateClockwise;
      
      return MallocCommand(currentTick + 2, args, 1, cfunc);
    }
  }
  return NULL;
}

Command* parseSonarToken(char** tokens, u32 tokenCt, u32 currentTick)
{
  if(tokenCt >= 2 &&
     !strcmp("list", tokens[0]) &&
     !strcmp("contacts", tokens[1]))
  {
    CommandFunc cfunc;

    cfunc.c0 = &Sonar_PrintContacts;
    return MallocCommand(currentTick + 2, NULL, 0, cfunc);
  }
  
  return NULL;
}

Command* parseFirstToken(char** tokens, u32 tokenCt,  u32 currentTick)
{
  if(tokenCt >= 1 &&
     !strcmp("helm", tokens[0]))
  {
    return parseHelmToken(tokens + 1, tokenCt - 1, currentTick);
  }
  else if(tokenCt >= 1 &&
	  !strcmp("sonar", tokens[0]))
  {
    return parseSonarToken(tokens + 1, tokenCt - 1, currentTick);
  }
  else if(tokenCt >= 1 &&
	  !strcmp("weapons", tokens[0]))
  {
    return parseWeaponsToken(tokens + 1, tokenCt - 1, currentTick);
  }

  return NULL;
}

Command* tokenparse(const char str[], u32 currentTick)
{
  const char delimiters[] = " \t.,;:!-";
  int delay = 0;
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

  return parseFirstToken(tokens, delimCt + 1, currentTick + delay); 
}
