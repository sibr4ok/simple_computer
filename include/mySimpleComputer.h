#ifndef MY_SIMPLE_COMPUTER_H
#define MY_SIMPLE_COMPUTER_H

#include "myTerm.h"

#define SC_MEMORY_SIZE 128

#define SC_FLAG_OVERFLOW 0x01
#define SC_FLAG_DIVISION_ZERO 0x02
#define SC_FLAG_OUT_OF_MEMORY 0x04
#define SC_FLAG_IGNORE_PULSE 0x08
#define SC_FLAG_INVALID_CMD 0x10

#define SC_RAW_MAX 0x7FFF
#define SC_VALUE_MAX 16383
#define SC_VALUE_MIN -16384

#define SC_SIGN_MASK 0x4000
#define SC_COMMAND_MASK 0x3F80
#define SC_OPERAND_MASK 0x007F

#define SC_CMD_NOP 0x00
#define SC_CMD_READ 0x10
#define SC_CMD_WRITE 0x11
#define SC_CMD_LOAD 0x20
#define SC_CMD_STORE 0x21
#define SC_CMD_ADD 0x30
#define SC_CMD_SUB 0x31
#define SC_CMD_DIVIDE 0x32
#define SC_CMD_MUL 0x33
#define SC_CMD_MOD 0x34
#define SC_CMD_JUMP 0x40
#define SC_CMD_JNEG 0x41
#define SC_CMD_JZ 0x42
#define SC_CMD_HALT 0x43
#define SC_CMD_NOT 0x51
#define SC_CMD_AND 0x52
#define SC_CMD_OR 0x53
#define SC_CMD_XOR 0x54
#define SC_CMD_JNS 0x55
#define SC_CMD_JC 0x56
#define SC_CMD_JNC 0x57
#define SC_CMD_JP 0x58
#define SC_CMD_JNP 0x59
#define SC_CMD_CHL 0x60
#define SC_CMD_CHR 0x61
#define SC_CMD_RCL 0x62
#define SC_CMD_RCR 0x63
#define SC_CMD_NEG 0x64
#define SC_CMD_ADDC 0x65
#define SC_CMD_SUBC 0x66
#define SC_CMD_LOGLC 0x67
#define SC_CMD_LOGRC 0x68
#define SC_CMD_RLOGCL 0x69
#define SC_CMD_RLOGCR 0x6A
#define SC_CMD_MWRITE 0x6B
#define SC_CMD_MREAD 0x6C

#define SC_VAL(sign, high, low) (((sign) << 14) | ((high) << 7) | (low))
#define SC_IC(low) ((low)&0x7F)

#define MEMORY_ROW 2
#define MEMORY_COL 1
#define MEMORY_COLS_NUM 10

#define ACC_LABEL_ROW 1
#define ACC_LABEL_COL 62
#define ACC_ROW 2
#define ACC_COL 62

#define FLAGS_LABEL_ROW 1
#define FLAGS_LABEL_COL 84
#define FLAGS_ROW 2
#define FLAGS_COL 84

#define IC_LABEL_ROW 3
#define IC_LABEL_COL 62
#define IC_ROW 4
#define IC_COL 62

#define CMD_LABEL_ROW 3
#define CMD_LABEL_COL 84
#define CMD_ROW 4
#define CMD_COL 84

#define INOUT_ROW 18
#define INOUT_COL 64
#define INOUT_LINES 5

#define DECODE_LABEL_ROW 15
#define DECODE_LABEL_COL 14
#define DECODE_ROW 16
#define DECODE_COL 1

#define EDITCELL_ROW 16
#define EDITCELL_COL 55

#define MIN_ROWS 25
#define MIN_COLS 100

int sc_from_decimal (int decimal);
int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);

int sc_regInit (void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);

int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);

int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);

int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandValidate (int command);

void printCell (int address, enum colors fg, enum colors bg);
void printFlags (void);
void printDecodedCommand (int value);
void printAccumulator (void);
void printCounters (void);
void printCommand (void);
void printTerm (int address, int input);

#endif