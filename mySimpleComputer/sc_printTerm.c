#include "sc.h"
#include <stdio.h>
#include <string.h>

static char inout_buf[INOUT_LINES][32];
static int inout_count = 0;

int
getInoutCount(void)
{
  return inout_count;
}

void
resetTerm (void)
{
  memset (inout_buf, 0, sizeof (inout_buf));
  inout_count = 0;

  for (int i = 0; i < INOUT_LINES; i++)
    {
      mt_gotoXY (INOUT_ROW + i, INOUT_COL);
      printf ("         ");
    }
  fflush (stdout);
}

void
printTerm (int address, int input)
{
  char line[32];

  if (input)
    {
      int raw;
      sc_memoryGet (address, &raw);
      int sign = (raw >> 14) & 0x01;
      int val = raw & 0x3FFF;
      snprintf (line, sizeof (line), "%02x< %c%04x", address,
                sign ? '-' : '+', val);
    }
  else
    {
      int raw;
      sc_memoryGet (address, &raw);
      int sign = (raw >> 14) & 0x01;
      int val = raw & 0x3FFF;
      snprintf (line, sizeof (line), "%02x> %c%04x", address,
                sign ? '-' : '+', val);
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

  mt_setfgcolor (GREEN);
  mt_setbgcolor (BLACK);
  for (int i = 0; i < inout_count; i++)
    {
      mt_gotoXY (INOUT_ROW + i, INOUT_COL);
      printf ("%-9s", inout_buf[i]);
    }
  fflush (stdout);
  mt_setdefaultcolor ();
}