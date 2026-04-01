CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include

TARGET = pr01
FONT_TARGET = font

SRCS = main.c
OBJS = $(SRCS:.c=.o)

SC_LIB = ../mySimpleComputer/libmySimpleComputer.a
MT_LIB = ../myTerm/libmyTerm.a
BC_LIB = ../myBigChars/libmyBigChars.a

all: $(TARGET) $(FONT_TARGET)

$(TARGET): $(OBJS) $(SC_LIB) $(MT_LIB) $(BC_LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -Wl,--start-group $(SC_LIB) $(MT_LIB) $(BC_LIB) -Wl,--end-group

$(FONT_TARGET): font.o $(BC_LIB) $(MT_LIB)
	$(CC) $(CFLAGS) -o $@ font.o -Wl,--start-group $(BC_LIB) $(MT_LIB) -Wl,--end-group

font.o: font.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SC_LIB):
	$(MAKE) -C ../mySimpleComputer

$(MT_LIB):
	$(MAKE) -C ../myTerm

$(BC_LIB):
	$(MAKE) -C ../myBigChars

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) font.o $(TARGET) $(FONT_TARGET)

.PHONY: all clean