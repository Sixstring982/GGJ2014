#include "command.h"

typedef struct s_departmentCommands
{
	int CommandSpace; 	//total number of department commands
	char * department;	//department name
	char *Commands[];	//list of commands
}DepartmentCommands;

