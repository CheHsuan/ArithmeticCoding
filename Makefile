CC = gcc
CFLAGS = --std gnu99 -O0 -Wall -g

EXEC = sample

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

all: libarith.o main.o
	$(CC) $(CFLAGS) -o $(EXEC) $^

debug:
	$(CC) $(CFLAGS) -DDEBUG -o $@ $^

clean:
	$(RM) $(EXEC) *.o
