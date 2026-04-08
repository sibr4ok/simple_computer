CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include
AR = ar
ARFLAGS = rcs

LIB = libmyReadKey.a

SRCS = rk_variables.c \
       rk_mytermsave.c \
       rk_mytermrestore.c \
       rk_mytermregime.c \
       rk_readkey.c \
       rk_readvalue.c

OBJS = $(SRCS:.c=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)

.PHONY: all clean