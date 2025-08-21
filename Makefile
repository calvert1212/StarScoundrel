CC=gcc
CFLAGS=-I/usr/include/ncurses
LDFLAGS=-lncurses -lSDL2 -lSDL2_mixer

SRCS = main.c game.c screens.c
OBJS = $(SRCS:.c=.o)

all: space_invaders

space_invaders: $(OBJS)
	$(CC) $(OBJS) -o space_invaders $(LDFLAGS)

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) space_invaders
