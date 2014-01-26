#ifndef CONSOLE_H
#define CONSOLE_H

#define TICK_SECS 5
#define MAX_BUFFER_LENGTH 1024

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


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
