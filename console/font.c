#include "myBigChars.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define FONT_SIZE 18

static int font[FONT_SIZE][2] = {
    /* 0: '0' */
    {0x66667E3C, 0x3C7E6666},
    /* 1: '1' */
    {0x18183818, 0x7E7E1818},
    /* 2: '2' */
    {0x06067E3C, 0x7E7E6030},
    /* 3: '3' */
    {0x1C06067E, 0x3C7E0606},
    /* 4: '4' */
    {0x7E666666, 0x0606067E},
    /* 5: '5' */
    {0x3E60607E, 0x3C7E0606},
    /* 6: '6' */
    {0x7E60663C, 0x3C66667E},
    /* 7: '7' */
    {0x0C06067E, 0x18181818},
    /* 8: '8' */
    {0x3C66663C, 0x3C66663C},
    /* 9: '9' */
    {0x7E66663C, 0x3C7E067E},
    /* 10: 'A' */
    {0x6666663C, 0x6666667E},
    /* 11: 'B' */
    {0x7C66667C, 0x7C66667C},
    /* 12: 'C' */
    {0x6060663C, 0x3C666060},
    /* 13: 'D' */
    {0x66666C78, 0x786C6666},
    /* 14: 'E' */
    {0x7C60607E, 0x7E60607C},
    /* 15: 'F' */
    {0x7C60607E, 0x60606060},
    /* 16: '+' */
    {0x7E181800, 0x0018187E},
    /* 17: '-' */
    {0x00000000, 0x00007E00},
};

int
main (void)
{
  int fd = open ("font.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0)
    {
      fprintf (stderr, "Ошибка: не удалось создать font.bin\n");
      return 1;
    }

  if (bc_bigcharwrite (fd, (int *)font, FONT_SIZE) != 0)
    {
      fprintf (stderr, "Ошибка: не удалось записать шрифт\n");
      close (fd);
      return 1;
    }

  close (fd);
  printf ("Шрифт записан в font.bin (%d символов)\n", FONT_SIZE);
  return 0;
}