.PHONY: clean all
CC=gcc
CFLAGS=-Wall -g
BIN=server client p2pServer p2pClient
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
