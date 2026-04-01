#include "myTerm.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
mt_gotoXY (int row, int col)
{
  if (row < 1 || col < 1)
    return -1;

  char seq[32];
  int len = snprintf (seq, sizeof (seq), "\033[%d;%dH", row, col);
  if (len < 0)
    return -1;
  if (write (STDOUT_FILENO, seq, len) == -1)
    return -1;
  return 0;
}