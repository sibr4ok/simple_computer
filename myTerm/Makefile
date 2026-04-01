CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include -I.
AR = ar
ARFLAGS = rcs

LIB = libmyTerm.a

SRCS = mt_clrscr.c \
       mt_gotoXY.c \
       mt_getscreensize.c \
       mt_setfgcolor.c \
       mt_setbgcolor.c \
       mt_setdefaultcolor.c \
       mt_setcursorvisible.c \
       mt_delline.c

OBJS = $(SRCS:.c=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)

.PHONY: all clean