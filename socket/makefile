.PHONY: clean all
CC=gcc
CFLAGS=-Wall -g
BIN=server client p2pServer p2pClient 01server 01client
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
