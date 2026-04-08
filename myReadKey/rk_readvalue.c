#include "myReadKey.h"
#include <stdio.h>
#include <unistd.h>

static int
key_to_hex (enum keys k)
{
  if (k >= KEY_0 && k <= KEY_9)
    return k - KEY_0;
  if (k >= KEY_A && k <= KEY_F)
    return 10 + (k - KEY_A);
  return -1;
}

static char
hex_char (int v)
{
  if (v >= 0 && v <= 9)
    return '0' + v;
  if (v >= 10 && v <= 15)
    return 'A' + (v - 10);
  return '0';
}

int
rk_readvalue (int *value, int timeout)
{
  if (value == NULL)
    return -1;

  if (timeout > 0)
    rk_mytermregime (1, timeout, 0, 0, 0);
  else
    rk_mytermregime (1, 0, 1, 0, 0);

  int sign = 0;
  int digits[4] = { 0, 0, 0, 0 };
  int pos = 0;
  int done = 0;
  int result = -1;

  printf ("+0000");
  fflush (stdout);
  printf ("\033[5D");
  fflush (stdout);

  while (!done)
    {
      enum keys key;
      int rc = rk_readkey (&key);

      if (rc != 0)
        continue;

      if (key == KEY_ESC)
        {
          result = 1;
          done = 1;
          break;
        }

      if (key == KEY_ENTER)
        {
          int high = (digits[0] << 4) | digits[1];
          int low = (digits[2] << 4) | digits[3];
          *value = (sign << 14) | (high << 7) | low;
          result = 0;
          done = 1;
          break;
        }

      if (pos == 0)
        {
          if (key == KEY_PLUS)
            {
              sign = 0;
              printf ("+");
              fflush (stdout);
              pos = 1;
            }
          else if (key == KEY_MINUS)
            {
              sign = 1;
              printf ("-");
              fflush (stdout);
              pos = 1;
            }
        }
      else if (pos >= 1 && pos <= 4)
        {
          int hv = key_to_hex (key);
          if (hv >= 0)
            {
              digits[pos - 1] = hv;
              printf ("%c", hex_char (hv));
              fflush (stdout);
              pos++;
              if (pos > 4)
                pos = 5;
            }
        }
    }

  rk_mytermregime (1, 0, 1, 0, 0);

  return result;
}