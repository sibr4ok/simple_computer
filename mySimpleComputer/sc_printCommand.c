#include "sc.h"
#include <stdio.h>

static void
printCommandDefaultError (void)
{
  /* IC некорректен или слово не декодируется вообще */
  printf ("! + FF : FF");
}

void
printCommand (void)
{
  int ic_val;
  sc_icounterGet (&ic_val);

  mt_gotoXY (CMD_ROW, CMD_COL);
  mt_setfgcolor (WHITE);
  mt_setbgcolor (BLACK);

  /* 1) Некорректный IC -> дефолт по ТЗ */
  if (ic_val < 0 || ic_val >= SC_MEMORY_SIZE)
    {
      printCommandDefaultError ();
      fflush (stdout);
      mt_setdefaultcolor ();
      return;
    }

  /* 2) Берём слово памяти по IC */
  int raw;
  if (sc_memoryGet (ic_val, &raw) != 0)
    {
      printCommandDefaultError ();
      fflush (stdout);
      mt_setdefaultcolor ();
      return;
    }

  /* 3) Декодируем поля (знак/код/операнд) */
  int sign, command, operand;
  if (sc_commandDecode (raw, &sign, &command, &operand) != 0)
    {
      printCommandDefaultError ();
      fflush (stdout);
      mt_setdefaultcolor ();
      return;
    }

  /* 4) Валидируем код операции строго по таблице */
  if (sc_commandValidate (command) != 0)
    {
      /* формат 2: показываем реальные поля, но с '!' */
      printf ("! %c %02X : %02X", sign ? '-' : '+', command, operand);
    }
  else
    {
      printf ("%c %02X : %02X", sign ? '-' : '+', command, operand);
    }

  fflush (stdout);
  mt_setdefaultcolor ();
}