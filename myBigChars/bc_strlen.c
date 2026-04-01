#include "myBigChars.h"
#include <stddef.h>

int
bc_strlen (char *str)
{
  if (str == NULL)
    return 0;

  int count = 0;
  unsigned char *p = (unsigned char *)str;

  while (*p)
    {
      if ((*p & 0x80) == 0)
        {
          p += 1;
        }
      else if ((*p & 0xE0) == 0xC0)
        {
          if ((p[1] & 0xC0) != 0x80)
            return 0;
          p += 2;
        }
      else if ((*p & 0xF0) == 0xE0)
        {
          if ((p[1] & 0xC0) != 0x80 || (p[2] & 0xC0) != 0x80)
            return 0;
          p += 3;
        }
      else if ((*p & 0xF8) == 0xF0)
        {
          if ((p[1] & 0xC0) != 0x80 || (p[2] & 0xC0) != 0x80
              || (p[3] & 0xC0) != 0x80)
            return 0;
          p += 4;
        }
      else
        {
          return 0;
        }
      count++;
    }
  return count;
}