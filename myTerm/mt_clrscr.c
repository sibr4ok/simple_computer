#include "myTerm.h"
#include <unistd.h>

int
mt_clrscr (void)
{
  char seq[] = "\033[2J\033[H";
  if (write (STDOUT_FILENO, seq, sizeof (seq) - 1) == -1)
    return -1;
  return 0;
}