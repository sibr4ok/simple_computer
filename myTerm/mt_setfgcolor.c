#include "myTerm.h"
#include <stdio.h>
#include <unistd.h>

int
mt_setfgcolor (enum colors color)
{
  if (color < BLACK || color > WHITE)
    return -1;

  char seq[16];
  int len = snprintf (seq, sizeof (seq), "\033[%dm", 30 + color);
  if (len < 0)
    return -1;
  if (write (STDOUT_FILENO, seq, len) == -1)
    return -1;
  return 0;
}