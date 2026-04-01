#include "sc.h"

int
sc_from_decimal (int decimal)
{
  int sign;
  int code;
  int high;
  int low;

  if (decimal >= 0)
    {
      sign = 0;
      code = decimal;
    }
  else
    {
      sign = 1;
      code = (1 << 14) + decimal;
    }

  if (code < 0 || code > 0x3FFF)
    return -1;

  high = (code >> 7) & 0x7F;
  low = code & 0x7F;

  return SC_VAL (sign, high, low);
}