#include "sc.h"
#include <stdio.h>

void
printCell (int address, enum colors fg, enum colors bg)
{
  if (address < 0 || address >= SC_MEMORY_SIZE)
    return;

  int row = MEMORY_ROW + (address / MEMORY_COLS_NUM);
  int col = MEMORY_COL + (address % MEMORY_COLS_NUM) * 6;

  mt_gotoXY (row, col);
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);

  int raw = sc_memory[address];
  int sign = (raw >> 14) & 0x01;
  int high7 = (raw >> 7) & 0x7F;
  int low7 = raw & 0x7F;

  printf ("%c%02X%02X", sign ? '-' : '+', high7, low7);
  fflush (stdout);
  mt_setdefaultcolor ();
}