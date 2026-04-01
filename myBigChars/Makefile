CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include
AR = ar
ARFLAGS = rcs

LIB = libmyBigChars.a

SRCS = bc_strlen.c \
       bc_printA.c \
       bc_box.c \
       bc_setbigcharpos.c \
       bc_getbigcharpos.c \
       bc_printbigchar.c \
       bc_bigcharwrite.c \
       bc_bigcharread.c

OBJS = $(SRCS:.c=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)

.PHONY: all clean