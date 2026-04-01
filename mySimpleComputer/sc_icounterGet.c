#include "sc.h"

int
sc_icounterGet (int *value)
{
  if (value == 0)
    return -1;
  *value = sc_icounter;
  return 0;
}