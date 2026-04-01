#include "sc.h"

int
sc_memoryGet (int address, int *value)
{
  if (address < 0 || address >= SC_MEMORY_SIZE)
    return -1;
  if (value == 0)
    return -1;

  *value = sc_memory[address];
  return 0;
}