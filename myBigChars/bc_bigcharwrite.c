#include "myBigChars.h"
#include <unistd.h>

int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (big == NULL || count <= 0)
    return -1;

  ssize_t total = (ssize_t)count * 2 * sizeof (int);
  ssize_t written = write (fd, big, total);
  if (written != total)
    return -1;

  return 0;
}