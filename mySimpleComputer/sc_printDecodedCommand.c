#include "sc.h"
#include <stdio.h>

void
printDecodedCommand (int raw)
{
  if (raw < 0 || raw > SC_RAW_MAX)
    return;

  int signed_val = sc_to_signed (raw);

  mt_gotoXY (DECODE_ROW, DECODE_COL);
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);

  if (signed_val < 0)
    printf ("dec: -%05d", -signed_val);
  else
    printf ("dec: %05d", signed_val);

  printf (" | oct: %05o", raw);
  printf (" | hex: %04X", raw);

  printf (" bin: ");
  printf ("%d ", (raw >> 14) & 1);
  for (int i = 13; i >= 7; i--)
    printf ("%d", (raw >> i) & 1);
  printf (" ");
  for (int i = 6; i >= 0; i--)
    printf ("%d", (raw >> i) & 1);

  fflush (stdout);
  mt_setdefaultcolor ();
}