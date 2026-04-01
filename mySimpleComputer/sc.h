#ifndef SC_INTERNAL_H
#define SC_INTERNAL_H

#include "mySimpleComputer.h"

extern int sc_memory[SC_MEMORY_SIZE];
extern int sc_flags;
extern int sc_accumulator;
extern int sc_icounter;

static inline int
sc_to_raw (int value)
{
  if (value >= 0)
    return value & 0x7FFF;
  else
    return ((~(-value)) + 1) & 0x7FFF;
}

static inline int
sc_to_signed (int raw)
{
  if ((raw & 0x4000) == 0)
    return raw;
  else
    return -(((~raw) + 1) & 0x7FFF);
}

#endif /* SC_INTERNAL_H */