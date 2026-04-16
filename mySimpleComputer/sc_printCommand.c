#include "sc.h"
#include <stdio.h>

static void
printCommandDefaultError (void)
{
  printf ("! + FF : FF");
}

static int
check_any_invalid_cmd (void)
{
  for (int i = 0; i < SC_MEMORY_SIZE; i++)
    {
      int raw;
      if (sc_memoryGet (i, &raw) != 0)
        continue;

      int sign, command, operand;
      if (sc_commandDecode (raw, &sign, &command, &operand) != 0)
        return 1;

      if (sc_commandValidate (command) != 0)
        return 1;
    }
  return 0;
}

void
printCommand (void)
{
  int ic_val;
  sc_icounterGet (&ic_val);

  if (check_any_invalid_cmd ())
    sc_regSet (SC_FLAG_INVALID_CMD, 1);
  else
    sc_regSet (SC_FLAG_INVALID_CMD, 0);

  mt_gotoXY (CMD_ROW, CMD_COL);
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);

  if (ic_val < 0 || ic_val >= SC_MEMORY_SIZE)
    {
      sc_regSet (SC_FLAG_OUT_OF_MEMORY, 1);
      printFlags ();
      mt_gotoXY (CMD_ROW, CMD_COL);
      mt_setfgcolor (WHITE);
      mt_setbgcolor (BLACK);
      printCommandDefaultError ();
      fflush (stdout);
      mt_setdefaultcolor ();
      return;
    }

  int raw;
  if (sc_memoryGet (ic_val, &raw) != 0)
    {
      sc_regSet (SC_FLAG_OUT_OF_MEMORY, 1);
      printFlags ();
      mt_gotoXY (CMD_ROW, CMD_COL);
      mt_setfgcolor (WHITE);
      mt_setbgcolor (BLACK);
      printCommandDefaultError ();
      fflush (stdout);
      mt_setdefaultcolor ();
      return;
    }

  sc_regSet (SC_FLAG_OUT_OF_MEMORY, 0);

  int sign, command, operand;
  if (sc_commandDecode (raw, &sign, &command, &operand) != 0)
    {
      printFlags ();
      mt_gotoXY (CMD_ROW, CMD_COL);
      mt_setfgcolor (WHITE);
      mt_setbgcolor (BLACK);
      printCommandDefaultError ();
      fflush (stdout);
      mt_setdefaultcolor ();
      return;
    }

  if (sc_commandValidate (command) != 0)
    {
      printFlags ();
      mt_gotoXY (CMD_ROW, CMD_COL);
      mt_setfgcolor (WHITE);
      mt_setbgcolor (BLACK);
      printf ("! %c %02X : %02X", sign ? '-' : '+', command, operand);
    }
  else
    {
      printFlags ();
      mt_gotoXY (CMD_ROW, CMD_COL);
      mt_setfgcolor (WHITE);
      mt_setbgcolor (BLACK);
      printf ("%c %02X : %02X", sign ? '-' : '+', command, operand);
    }

  fflush (stdout);
  mt_setdefaultcolor ();
}