#include <string.h>
#include <stddef.h>
#include <stdio.h>

#include "parse.h"
#include "command.h"

Command * parse(char **, int size)
{
	int delay = 0;

  	/* look for delay syntax */
  	char * cmp[] = "delay";
  	for( int i = 0; i < numtokens; i++)
  	{
   	 	if(!strcmp(numtokens[i],cmp))
      	delay = atoi(numtokens[++i]);
  	}
}
