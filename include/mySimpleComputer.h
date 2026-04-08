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

/* Команды строго по таблице (hex-коды) */
#define SC_CMD_NOP 0x00
#define SC_CMD_CPUINFO 0x01

#define SC_CMD_READ 0x0A
#define SC_CMD_WRITE 0x0B

#define SC_CMD_LOAD 0x14
#define SC_CMD_STORE 0x15

#define SC_CMD_ADD 0x1E
#define SC_CMD_SUB 0x1F
#define SC_CMD_DIVIDE 0x20
#define SC_CMD_MUL 0x21

#define SC_CMD_JUMP 0x28
#define SC_CMD_JNEG 0x29
#define SC_CMD_JZ 0x2A
#define SC_CMD_HALT 0x2B

#define SC_CMD_NOT 0x33
#define SC_CMD_AND 0x34
#define SC_CMD_OR 0x35
#define SC_CMD_XOR 0x36
#define SC_CMD_JNS 0x37
#define SC_CMD_JC 0x38
#define SC_CMD_JNC 0x39
#define SC_CMD_JP 0x3A
#define SC_CMD_JNP 0x3B
#define SC_CMD_CHL 0x3C
#define SC_CMD_SHR 0x3D
#define SC_CMD_RCL 0x3E
#define SC_CMD_RCR 0x3F
#define SC_CMD_NEG 0x40
#define SC_CMD_ADDC 0x41
#define SC_CMD_SUBC 0x42
#define SC_CMD_LOGLC 0x43
#define SC_CMD_LOGRC 0x44
#define SC_CMD_RCCL 0x45
#define SC_CMD_RCCR 0x46
#define SC_CMD_MOVA 0x47
#define SC_CMD_MOVR 0x48
#define SC_CMD_MOVCA 0x49
#define SC_CMD_MOVCR 0x4A
#define SC_CMD_ADDCM 0x4B
#define SC_CMD_SUBCM 0x4C

#define SC_VAL(sign, high, low) (((sign) << 14) | ((high) << 7) | (low))
#define SC_IC(low) ((low)&0x7F)

#define MEMORY_ROW 2
#define MEMORY_COL 2
#define MEMORY_COLS_NUM 10

#define ACC_ROW 2
#define ACC_COL 64

#define FLAGS_ROW 2
#define FLAGS_COL 90

#define IC_ROW 5
#define IC_COL 65

#define CMD_ROW 5
#define CMD_COL 90

#define INOUT_ROW 20
#define INOUT_COL 64
#define INOUT_LINES 5

#define DECODE_ROW 17
#define DECODE_COL 2

#define EDITCELL_ROW 16
#define EDITCELL_COL 55

#define MIN_ROWS 28
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