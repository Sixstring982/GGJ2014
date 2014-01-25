#ifndef CONSOLE_H
#define CONSOLE_H

#define TICK_SECS 5

#include "itype.h"

/* Blocks stdin for TICK_SECS seconds. */
/* Returns true if there is readable data */
/* from stdin. */
extern bool ConsoleDataAvailable();

/* Fills toBuffer with the next available */
/* newline delimited string from stdin. */
extern void ReadLine(char* toBuffer);

#endif /*CONSOLE_H*/
