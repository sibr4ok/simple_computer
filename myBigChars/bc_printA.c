#include "myBigChars.h"
#include <stdio.h>
#include <unistd.h>

int
bc_printA (char *str)
{
  if (str == NULL)
    return -1;

  /* Enter alternate charset mode */
  if (write (STDOUT_FILENO, "\033(0", 3) == -1)
    return -1;

  while (*str)
    {
      if (write (STDOUT_FILENO, str, 1) == -1)
        {
          write (STDOUT_FILENO, "\033(B", 3);
          return -1;
        }
      str++;
    }

  /* Exit alternate charset mode */
  if (write (STDOUT_FILENO, "\033(B", 3) == -1)
    return -1;

  return 0;
}