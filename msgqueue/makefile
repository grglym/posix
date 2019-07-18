

client: comm.o client.o
	cc -o client comm.o client.o

server: comm.o server.o
	cc -o server comm.o server.o

server.o: comm.h server.c
	cc -c server.c


client.o: comm.h client.c
	cc -c client.c

comm.o: comm.c comm.h
	cc -c comm.c
