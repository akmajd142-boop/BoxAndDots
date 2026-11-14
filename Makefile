CC = gcc
CFLAGS = -Wall -Wextra -g

OBJS = main.o game.o display.o input.o

all: dotsandboxes

dotsandboxes: $(OBJS)
	$(CC) $(CFLAGS) -o dotsandboxes $(OBJS)

main.o: main.c game.h display.h input.h board.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h board.h
	$(CC) $(CFLAGS) -c game.c

display.o: display.c display.h board.h
	$(CC) $(CFLAGS) -c display.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

test: test_game.c game.c game.h board.h
	$(CC) $(CFLAGS) -o test_game test_game.c game.c
	./test_game

clean:
	rm -f $(OBJS) dotsandboxes test_game

.PHONY: all test clean
