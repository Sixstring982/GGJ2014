#ifndef CONSOLE_H
#define CONSOLE_H

#define TICK_SECS 5
#define MAX_BUFFER_LENGTH 1024

#include "itype.h"

/* Blocks stdin for TICK_SECS seconds.    */
/* Returns true if there is readable data */
/* from stdin.                            */
extern bool Console_DataAvailable();

/* Fills toBuffer with the next available */
/* newline delimited string from stdin.   */
/* The resulting data in toBuffer will be */
/* null terminated and won't contain the  */
/* newline character.                     */
extern void Console_ReadLine(char* toBuffer);

#endif /*CONSOLE_H*/
