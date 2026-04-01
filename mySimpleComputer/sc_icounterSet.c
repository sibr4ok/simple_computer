#include "sc.h"

int
sc_icounterSet (int value)
{
  if (value < 0 || value > SC_RAW_MAX)
    return -1;
  sc_icounter = value;
  return 0;
}