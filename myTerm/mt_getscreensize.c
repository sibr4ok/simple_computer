#include "myTerm.h"
#include <sys/ioctl.h>
#include <unistd.h>

int
mt_getscreensize (int *rows, int *cols)
{
  if (rows == NULL || cols == NULL)
    return -1;

  struct winsize ws;
  if (ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
    return -1;

  *rows = ws.ws_row;
  *cols = ws.ws_col;
  return 0;
}