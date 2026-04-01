#include "sc.h"

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (value == 0)
    return -1;

  if (sign != 0 && sign != 1)
    return -1;

  if (command < 0 || command > 0x7F)
    return -1;

  if (operand < 0 || operand > 0x7F)
    return -1;

  *value = (sign << 14) | (command << 7) | operand;
  return 0;
}