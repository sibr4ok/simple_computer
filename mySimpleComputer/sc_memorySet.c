#include "sc.h"

int
sc_memorySet (int address, int value)
{
  if (address < 0 || address >= SC_MEMORY_SIZE)
    return -1;

  if (value < 0 || value > SC_RAW_MAX)
    return -1;

  sc_memory[address] = value;
  return 0;
}