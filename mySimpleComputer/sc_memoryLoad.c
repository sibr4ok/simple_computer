#include "sc.h"
#include <stdio.h>

int
sc_memoryLoad (char *filename)
{
  if (filename == NULL)
    return -1;

  FILE *f = fopen (filename, "rb");
  if (f == NULL)
    return -1;

  int temp[SC_MEMORY_SIZE];
  size_t count = fread (temp, sizeof (int), SC_MEMORY_SIZE, f);
  fclose (f);

  if (count != SC_MEMORY_SIZE)
    return -1;

  for (int i = 0; i < SC_MEMORY_SIZE; i++)
    sc_memory[i] = temp[i];

  return 0;
}