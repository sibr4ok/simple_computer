#include "sc.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (sign == 0 || command == 0 || operand == 0)
    return -1;

  if (value < 0 || value > SC_RAW_MAX)
    return -1;

  *sign = (value >> 14) & 0x01;
  *command = (value >> 7) & 0x7F;
  *operand = value & 0x7F;
  return 0;
}