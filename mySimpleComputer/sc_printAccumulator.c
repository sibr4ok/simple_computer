#include "sc.h"
#include <stdio.h>

void
printAccumulator (void)
{
  int raw = sc_accumulator;
  int sign = (raw >> 14) & 0x01;
  int high7 = (raw >> 7) & 0x7F;
  int low7 = raw & 0x7F;

  mt_gotoXY (ACC_ROW, ACC_COL);
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);            // ← ДОБАВИТЬ
  printf ("sc: %c%02X%02X hex: %04X", sign ? '-' : '+', high7, low7, raw);
  fflush (stdout);
  mt_setdefaultcolor ();
}