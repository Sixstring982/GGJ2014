#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{
  fd_set rfds;
  struct timeval tv;
  int retval;

  FD_ZERO(&rfds);
  FD_SET(0, &rfds);

  tv.tv_sec = TICK_SECS;
  tv.tv_usec = TICK_USECS;

  retval = select(1, &rfds, NULL, NULL, &tv);

  if(retval == -1)
  {
    perror("select() failed!\n");
  }
  else if(retval)
  {
    printf("Data is available.\n");
  }
  else
  {
    printf("No data available.\n");
  }

  exit(EXIT_SUCCESS);
}
