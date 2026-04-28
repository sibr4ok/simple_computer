#include "sc.h"

int
sc_commandValidate (int command)
{
  switch (command)
    {
    case SC_CMD_NOP:
    case SC_CMD_CPUINFO:

    case SC_CMD_READ:
    case SC_CMD_WRITE:

    case SC_CMD_LOAD:
    case SC_CMD_STORE:

    case SC_CMD_ADD:
    case SC_CMD_SUB:
    case SC_CMD_DIVIDE:
    case SC_CMD_MUL:

    case SC_CMD_JUMP:
    case SC_CMD_JNEG:
    case SC_CMD_JZ:
    case SC_CMD_HALT:

    case SC_CMD_NOT:
    case SC_CMD_AND:
    case SC_CMD_OR:
    case SC_CMD_XOR:
      return 0;

    default:
      return -1;
    }
}