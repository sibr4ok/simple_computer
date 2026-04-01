#include "myBigChars.h"

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (big == 0 || x < 0 || x > 7 || y < 0 || y > 7)
    return -1;

  int idx = x / 4;
  int bit_row = x % 4;
  int bit_pos = bit_row * 8 + y;

  if (value)
    big[idx] |= (1 << bit_pos);
  else
    big[idx] &= ~(1 << bit_pos);

  return 0;
}