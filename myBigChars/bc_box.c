#include "myBigChars.h"
#include <stdio.h>
#include <unistd.h>

int
bc_box (int x1, int y1, int x2, int y2, enum colors box_fg,
        enum colors box_bg, char *header, enum colors header_fg,
        enum colors header_bg)
{
  if (x2 < 2 || y2 < 2)
    return -1;

  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);

  /* Top line */
  mt_gotoXY (x1, y1);
  write (STDOUT_FILENO, "\033(0", 3);
  write (STDOUT_FILENO, "l", 1);
  for (int i = 0; i < y2 - 2; i++)
    write (STDOUT_FILENO, "q", 1);
  write (STDOUT_FILENO, "k", 1);
  write (STDOUT_FILENO, "\033(B", 3);

  /* Side lines */
  for (int r = 1; r < x2 - 1; r++)
    {
      mt_gotoXY (x1 + r, y1);
      write (STDOUT_FILENO, "\033(0", 3);
      write (STDOUT_FILENO, "x", 1);
      write (STDOUT_FILENO, "\033(B", 3);

      for (int c = 0; c < y2 - 2; c++)
        write (STDOUT_FILENO, " ", 1);

      write (STDOUT_FILENO, "\033(0", 3);
      write (STDOUT_FILENO, "x", 1);
      write (STDOUT_FILENO, "\033(B", 3);
    }

  /* Bottom line */
  mt_gotoXY (x1 + x2 - 1, y1);
  write (STDOUT_FILENO, "\033(0", 3);
  write (STDOUT_FILENO, "m", 1);
  for (int i = 0; i < y2 - 2; i++)
    write (STDOUT_FILENO, "q", 1);
  write (STDOUT_FILENO, "j", 1);
  write (STDOUT_FILENO, "\033(B", 3);

  /* Header */
  if (header != NULL)
    {
      int hlen = bc_strlen (header);
      if (hlen > 0 && hlen <= y2 - 2)
        {
          int hpos = y1 + 1 + (y2 - 2 - hlen) / 2;
          mt_gotoXY (x1, hpos);
          mt_setfgcolor (header_fg);
          mt_setbgcolor (header_bg);
          printf ("%s", header);
          fflush (stdout);
        }
    }

  mt_setdefaultcolor ();
  return 0;
}