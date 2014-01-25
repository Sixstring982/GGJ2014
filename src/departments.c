#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "departments.h"

#define NUMDEPARTMENTS 10
#define COMMANDLIMIT 32


Department * MallocDepartments( int space, char * name,  char ** cmds, int commandlimit) 
{	
  Department *department = (Department *) malloc(sizeof(Department));
  department-> commandspace = space;
  department -> departmentname = name;
  memcpy(department -> commands, cmds, commandlimit * sizeof(char *) );
  
  return department;
}

