#include "myReadKey.h"
#include <unistd.h>

int
rk_readkey (enum keys *key)
{
  unsigned char buf[16];
  ssize_t n;

  if (key == NULL)
    return -1;

  *key = KEY_NONE;

  n = read (STDIN_FILENO, buf, sizeof (buf));
  if (n <= 0)
    return -1;

  if (n == 1)
    {
      unsigned char c = buf[0];

      if (c == 27)
        {
          *key = KEY_ESC;
          return 0;
        }
      if (c == '\n' || c == '\r')
        {
          *key = KEY_ENTER;
          return 0;
        }
      if (c == '+')
        {
          *key = KEY_PLUS;
          return 0;
        }
      if (c == '-')
        {
          *key = KEY_MINUS;
          return 0;
        }

      if (c >= '0' && c <= '9')
        {
          *key = KEY_0 + (c - '0');
          return 0;
        }
      if (c >= 'a' && c <= 'f')
        {
          *key = KEY_A + (c - 'a');
          return 0;
        }
      if (c >= 'A' && c <= 'F')
        {
          *key = KEY_A + (c - 'A');
          return 0;
        }

      if (c == 'l' || c == 'L')
        {
          *key = KEY_L;
          return 0;
        }
      if (c == 's' || c == 'S')
        {
          *key = KEY_S;
          return 0;
        }
      if (c == 'i' || c == 'I')
        {
          *key = KEY_I;
          return 0;
        }
      if (c == 'r' || c == 'R')
        {
          *key = KEY_R;
          return 0;
        }
      if (c == 't' || c == 'T')
        {
          *key = KEY_T;
          return 0;
        }

      *key = KEY_OTHER;
      return 0;
    }

  if (buf[0] == 27 && n >= 3 && buf[1] == '[')
    {
      if (n == 3)
        {
          switch (buf[2])
            {
            case 'A':
              *key = KEY_UP;
              return 0;
            case 'B':
              *key = KEY_DOWN;
              return 0;
            case 'C':
              *key = KEY_RIGHT;
              return 0;
            case 'D':
              *key = KEY_LEFT;
              return 0;
            }
        }

      if (n == 5 && buf[2] == '1' && buf[3] == '5' && buf[4] == '~')
        {
          *key = KEY_F5;
          return 0;
        }

      if (n == 5 && buf[2] == '1' && buf[3] == '7' && buf[4] == '~')
        {
          *key = KEY_F6;
          return 0;
        }

      if (n == 4 && buf[2] == '[' && buf[3] == 'E')
        {
          *key = KEY_F5;
          return 0;
        }
    }

  if (buf[0] == 27 && n >= 3 && buf[1] == 'O')
    {
      switch (buf[2])
        {
        case 'A':
          *key = KEY_UP;
          return 0;
        case 'B':
          *key = KEY_DOWN;
          return 0;
        case 'C':
          *key = KEY_RIGHT;
          return 0;
        case 'D':
          *key = KEY_LEFT;
          return 0;
        }
    }

  *key = KEY_OTHER;
  return 0;
}