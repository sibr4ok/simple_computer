#include "sc.h"

int
sc_regSet (int reg, int value)
{
  if (reg != SC_FLAG_OVERFLOW && reg != SC_FLAG_DIVISION_ZERO
      && reg != SC_FLAG_OUT_OF_MEMORY && reg != SC_FLAG_IGNORE_PULSE
      && reg != SC_FLAG_INVALID_CMD)
    return -1;

  if (value)
    sc_flags |= reg;
  else
    sc_flags &= ~reg;

  return 0;
}