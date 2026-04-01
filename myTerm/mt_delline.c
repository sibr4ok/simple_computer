#include "myTerm.h"
#include <unistd.h>

int
mt_delline (void)
{
  char seq[] = "\033[2K";
  if (write (STDOUT_FILENO, seq, sizeof (seq) - 1) == -1)
    return -1;
  return 0;
}