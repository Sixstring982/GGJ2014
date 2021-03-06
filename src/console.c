#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include "console.h"

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

#define COLOR_RED_HIGH     "\033[91m"      /* Red background */

#define COLOR_BACK_RED_HIGH     "\033[101m"      /* Red background */

/* printf( COLOR_GREEN "Here is some text\n" COLOR_RESET ); */

void Console_ColorBasedOnValue(u32 val, u32 min, u32 max)
{
  if(val > (3*max/4 - min))
    printf(COLOR_GREEN );
  else if(val > (max/3 -min) )
    printf(COLOR_YELLOW );
  else
    printf(COLOR_RED);
  return;
}

static u32 tickSecs = TICK_SECS;
bool Console_DataAvailable()
{
  fd_set rfds;
  struct timeval tv;
  int retval;

  FD_ZERO(&rfds);
  FD_SET(0, &rfds);

  tv.tv_sec = tickSecs;
  tv.tv_usec = 0;

  retval = select(1, &rfds, NULL, NULL, &tv);

  switch(retval)
  {
  case -1: perror("IOError in select!\n"); exit(5); return false;
  case 0:  return false;
  default:  return true;
  }
  
}

void Console_IncreaseTickSpeed()
{
  tickSecs--;
}

u32 Console_GetTickSpeed()
{
  return tickSecs;
}

void Console_ReadLine(char* toBuffer)
{
  int readC;
  s32 i;
  for(i = 0; i < MAX_BUFFER_LENGTH; i++)
  {
    switch((readC = fgetc(stdin)))
    {
    case '\n': toBuffer[i] = 0; return;
    default: toBuffer[i] = readC; break;
    }
  }
}
