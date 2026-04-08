#include "myReadKey.h"
#include <termios.h>
#include <unistd.h>

extern struct termios rk_saved_termios;
extern int rk_saved_valid;

int
rk_mytermsave (void)
{
  if (tcgetattr (STDIN_FILENO, &rk_saved_termios) != 0)
    return -1;
  rk_saved_valid = 1;
  return 0;
}