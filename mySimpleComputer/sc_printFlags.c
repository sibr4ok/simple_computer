#include "sc.h"
#include <stdio.h>

void
printFlags (void)
{
  int v;

  mt_gotoXY (FLAGS_ROW, FLAGS_COL);
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);           

  sc_regGet (SC_FLAG_OVERFLOW, &v);
  printf ("%c ", v ? 'P' : '_');
  sc_regGet (SC_FLAG_DIVISION_ZERO, &v);
  printf ("%c ", v ? '0' : '_');
  sc_regGet (SC_FLAG_OUT_OF_MEMORY, &v);
  printf ("%c ", v ? 'M' : '_');
  sc_regGet (SC_FLAG_IGNORE_PULSE, &v);
  printf ("%c ", v ? 'T' : '_');
  sc_regGet (SC_FLAG_INVALID_CMD, &v);
  printf ("%c", v ? 'E' : '_');

  fflush (stdout);
  mt_setdefaultcolor ();
}