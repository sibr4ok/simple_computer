#include "myTerm.h"
#include <string.h>
#include <unistd.h>

int
mt_setcursorvisible (int value)
{
  if (value)
    {
      char seq[] = "\033[?25h";
      if (write (STDOUT_FILENO, seq, strlen (seq)) == -1)
        return -1;
    }
  else
    {
      char seq[] = "\033[?25l";
      if (write (STDOUT_FILENO, seq, strlen (seq)) == -1)
        return -1;
    }
  return 0;
}