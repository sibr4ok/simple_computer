#include "sc.h"
#include <stdio.h>

int
sc_memorySave (char *filename)
{
  if (filename == NULL)
    return -1;

  FILE *f = fopen (filename, "wb");
  if (f == NULL)
    return -1;

  size_t written = fwrite (sc_memory, sizeof (int), SC_MEMORY_SIZE, f);
  fclose (f);

  if (written != SC_MEMORY_SIZE)
    return -1;

  return 0;
}