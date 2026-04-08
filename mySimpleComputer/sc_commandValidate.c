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
    case SC_CMD_JNS:
    case SC_CMD_JC:
    case SC_CMD_JNC:
    case SC_CMD_JP:
    case SC_CMD_JNP:
    case SC_CMD_CHL:
    case SC_CMD_SHR:
    case SC_CMD_RCL:
    case SC_CMD_RCR:
    case SC_CMD_NEG:
    case SC_CMD_ADDC:
    case SC_CMD_SUBC:
    case SC_CMD_LOGLC:
    case SC_CMD_LOGRC:
    case SC_CMD_RCCL:
    case SC_CMD_RCCR:
    case SC_CMD_MOVA:
    case SC_CMD_MOVR:
    case SC_CMD_MOVCA:
    case SC_CMD_MOVCR:
    case SC_CMD_ADDCM:
    case SC_CMD_SUBCM:
      return 0;

    default:
      return -1;
    }
}