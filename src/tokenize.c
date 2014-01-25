#include <string.h>
#include <stddef.h>
#include <stdio.h>

#include "tokenize.h"
#include "command.h"

Command * tokenize(const char string[] )
{
     int max_list_size = 64;

     const char delimiters[] = " \t.,;:!-";
     char *running;
     char *token;

     char **tmp, *tokenv[max_list_size];

     running = strdup (string);

     int numtokens = 0;
     for (tmp = tokenv; (*tmp = strsep(&running, delimiters)) != NULL; numtokens++)
          if (**tmp != '\0')
               if (++tmp >= &tokenv[max_list_size])
                   break;

     
}
     
