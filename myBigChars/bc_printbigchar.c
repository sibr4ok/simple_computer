#include "myBigChars.h"
#include <stdio.h>
#include <unistd.h>

int
bc_printbigchar (int big[2], int x, int y, enum colors fg, enum colors bg)
{
  if (big == NULL)
    return -1;

  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  for (int row = 0; row < 8; row++)
    {
      mt_gotoXY (x + row, y);

      int idx = row / 4;      
      int bit_row = row % 4;
      int byte_val = (big[idx] >> (bit_row * 8)) & 0xFF;

      for (int col = 7; col >= 0; col--)  
        {
          int bit = (byte_val >> col) & 1;
          if (bit)
            {
              write (STDOUT_FILENO, "\033(0", 3);
              write (STDOUT_FILENO, "a", 1);
              write (STDOUT_FILENO, "\033(B", 3);
            }
          else
            {
              write (STDOUT_FILENO, " ", 1);
            }
        }
    }

  mt_setdefaultcolor ();
  return 0;
}