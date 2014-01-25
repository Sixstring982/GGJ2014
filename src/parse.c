#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "command.h"

Command * parse(char ** tokenv, int size)
{
	int delay = 0;

  	/* look for delay syntax */
  	char cmp[] = "delay";
  	int i;
  	for(i = 0; i < size; i++)
  	{
   	 	if(!strcmp(tokenv[i],cmp))
      	delay = atoi(tokenv[++i]);
  	}

  	return NULL;
}
