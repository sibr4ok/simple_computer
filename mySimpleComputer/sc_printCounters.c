#include "sc.h"
#include <stdio.h>

void
printCounters (void)
{
  int raw = sc_icounter;
  int sign = (raw >> 14) & 0x01;
  int high7 = (raw >> 7) & 0x7F;
  int low7 = raw & 0x7F;

  mt_gotoXY (IC_ROW, IC_COL);
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);            // ← ДОБАВИТЬ
  printf ("T: %02d     IC: %c%02X%02X", 0, sign ? '-' : '+', high7, low7);
  fflush (stdout);
  mt_setdefaultcolor ();
}