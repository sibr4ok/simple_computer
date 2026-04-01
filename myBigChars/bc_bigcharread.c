#include "myBigChars.h"
#include <unistd.h>

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  if (big == NULL || count == NULL || need_count <= 0)
    {
      if (count)
        *count = 0;
      return -1;
    }

  ssize_t total = (ssize_t)need_count * 2 * sizeof (int);
  ssize_t rd = read (fd, big, total);

  if (rd <= 0)
    {
      *count = 0;
      return -1;
    }

  *count = (int)(rd / (2 * sizeof (int)));
  if (*count == 0)
    return -1;

  return 0;
}