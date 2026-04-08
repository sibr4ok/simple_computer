#include "myReadKey.h"
#include <termios.h>
#include <unistd.h>

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios t;
  if (tcgetattr (STDIN_FILENO, &t) != 0)
    return -1;

  if (regime == 0)
    {
      /* Канонический режим */
      t.c_lflag |= ICANON;
    }
  else
    {
      /* Неканонический режим */
      t.c_lflag &= ~ICANON;
      t.c_cc[VTIME] = vtime;
      t.c_cc[VMIN] = vmin;
    }

  if (echo)
    t.c_lflag |= ECHO;
  else
    t.c_lflag &= ~ECHO;

  if (sigint)
    t.c_lflag |= ISIG;
  else
    t.c_lflag &= ~ISIG;

  if (tcsetattr (STDIN_FILENO, TCSANOW, &t) != 0)
    return -1;

  return 0;
}