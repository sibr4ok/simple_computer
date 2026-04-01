#include "sc.h"

int
sc_regInit (void)
{
  sc_flags = SC_FLAG_IGNORE_PULSE;
  return 0;
}