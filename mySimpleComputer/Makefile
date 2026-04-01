CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include -I.
AR = ar
ARFLAGS = rcs

LIB = libmySimpleComputer.a

SRCS = sc_variables.c \
       sc_memoryInit.c \
       sc_memorySet.c \
       sc_memoryGet.c \
       sc_memorySave.c \
       sc_memoryLoad.c \
       sc_regInit.c \
       sc_regSet.c \
       sc_regGet.c \
       sc_accumulatorInit.c \
       sc_accumulatorSet.c \
       sc_accumulatorGet.c \
       sc_icounterInit.c \
       sc_icounterSet.c \
       sc_icounterGet.c \
       sc_commandEncode.c \
       sc_commandDecode.c \
       sc_commandValidate.c \
       sc_printCell.c \
       sc_printFlags.c \
       sc_printDecodedCommand.c \
       sc_printAccumulator.c \
       sc_printCounters.c \
       sc_printCommand.c \
       sc_printTerm.c \
       sc_fromDecimal.c

OBJS = $(SRCS:.c=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)

.PHONY: all clean