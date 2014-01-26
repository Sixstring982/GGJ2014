#ifndef CONSOLE_H
#define CONSOLE_H

#define TICK_SECS 5
#define MAX_BUFFER_LENGTH 1024

#define TEXT_RESET   "\033[0m"
#define TEXT_BLINK    "\033[5m"      /* BLINK */
#define TEXT_BLINKOFF   "\033[25m"      /* NO BLINK */

#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[30m"      /* Black */
#define COLOR_RED     "\033[31m"      /* Red */
#define COLOR_GREEN   "\033[32m"      /* Green */
#define COLOR_YELLOW  "\033[33m"      /* Yellow */
#define COLOR_BLUE    "\033[34m"      /* Blue */
#define COLOR_MAGENTA "\033[35m"      /* Magenta */
#define COLOR_CYAN    "\033[36m"      /* Cyan */
#define COLOR_WHITE   "\033[37m"      /* White */
#define COLOR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define COLOR_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define COLOR_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define COLOR_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define COLOR_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define COLOR_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define COLOR_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define COLOR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define COLOR_BACK_RED     "\033[41m"      /* Red background */
#define COLOR_BACK_RESET    "\033[40m"      /* reset background */

#define COLOR_BACK_RED_HIGH     "\033[101m"      /* Red background */



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
