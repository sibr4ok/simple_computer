#include "sc.h"
#include <stdio.h>

void
printCommand (void)
{
  int ic_val;
  sc_icounterGet (&ic_val);

  mt_gotoXY (CMD_ROW, CMD_COL);
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);

  if (ic_val < 0 || ic_val >= SC_MEMORY_SIZE)
    {
      printf ("! + FF : FF");
      fflush (stdout);
      mt_setdefaultcolor ();
      return;
    }

  int raw;
  sc_memoryGet (ic_val, &raw);

  int sign, command, operand;
  if (sc_commandDecode (raw, &sign, &command, &operand) != 0)
    {
      printf ("! + FF : FF");
      fflush (stdout);
      mt_setdefaultcolor ();
      return;
    }

  printf ("%c %02X : %02X", sign ? '-' : '+', command, operand);
  fflush (stdout);
  mt_setdefaultcolor ();
}