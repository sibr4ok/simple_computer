#include "myTerm.h"
#include <unistd.h>

int
mt_setdefaultcolor (void)
{
  char seq[] = "\033[0m";
  if (write (STDOUT_FILENO, seq, sizeof (seq) - 1) == -1)
    return -1;
  return 0;
}