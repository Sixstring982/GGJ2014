#include "command.h"

#define COMMANDLIMIT 32

typedef struct s_departmentCommands
{
  int commandspace;  		  /*total number of department commands */
  char * departmentname;	  /*department name */
  char *commands[COMMANDLIMIT];	  /*list of commands */
}Department;

