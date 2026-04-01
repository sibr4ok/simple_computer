#include "sc.h"

int
sc_regGet (int reg, int *value)
{
  if (value == 0)
    return -1;

  if (reg != SC_FLAG_OVERFLOW && reg != SC_FLAG_DIVISION_ZERO
      && reg != SC_FLAG_OUT_OF_MEMORY && reg != SC_FLAG_IGNORE_PULSE
      && reg != SC_FLAG_INVALID_CMD)
    return -1;

  *value = (sc_flags & reg) ? 1 : 0;
  return 0;
}