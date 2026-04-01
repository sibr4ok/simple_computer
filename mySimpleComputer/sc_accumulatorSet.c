#include "sc.h"

int
sc_accumulatorSet (int value)
{
  if (value < 0 || value > SC_RAW_MAX)
    return -1;
  sc_accumulator = value;
  return 0;
}