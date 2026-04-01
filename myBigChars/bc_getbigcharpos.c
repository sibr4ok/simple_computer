#include "myBigChars.h"

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (big == 0 || value == 0 || x < 0 || x > 7 || y < 0 || y > 7)
    return -1;

  int idx = x / 4;
  int bit_row = x % 4;
  int bit_pos = bit_row * 8 + y;

  *value = (big[idx] >> bit_pos) & 1;
  return 0;
}