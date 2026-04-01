#include "sc.h"
#include <stdio.h>
#include <string.h>

static char inout_buf[INOUT_LINES][32];
static int inout_count = 0;

void
printTerm (int address, int input)
{
  char line[32];

  if (input)
    {
      snprintf (line, sizeof (line), "%02X> ",
                address); 
    }
  else
    {
      int raw;
      sc_memoryGet (address, &raw);
      int sign = (raw >> 14) & 0x01;
      int high7 = (raw >> 7) & 0x7F;
      int low7 = raw & 0x7F;
      snprintf (line, sizeof (line), "%02X> %c%02X%02X", address,
                sign ? '-' : '+', high7, low7); 
    }

  if (inout_count < INOUT_LINES)
    {
      snprintf (inout_buf[inout_count], sizeof (inout_buf[0]), "%s", line);
      inout_count++;
    }
  else
    {
      memmove (inout_buf[0], inout_buf[1],
               sizeof (inout_buf[0]) * (INOUT_LINES - 1));
      snprintf (inout_buf[INOUT_LINES - 1], sizeof (inout_buf[0]), "%s", line);
    }

  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);
  for (int i = 0; i < inout_count; i++)
    {
      mt_gotoXY (INOUT_ROW + i, INOUT_COL);
      printf ("%-9s", inout_buf[i]);
    }
  fflush (stdout);
  mt_setdefaultcolor ();
}