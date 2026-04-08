#include "myReadKey.h"
#include <termios.h>
#include <unistd.h>

extern struct termios rk_saved_termios;
extern int rk_saved_valid;

int
rk_mytermrestore (void)
{
  if (!rk_saved_valid)
    return -1;
  if (tcsetattr (STDIN_FILENO, TCSANOW, &rk_saved_termios) != 0)
    return -1;
  return 0;
}