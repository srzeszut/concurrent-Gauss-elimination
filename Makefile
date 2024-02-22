
CC = gcc
CFLAGS = -Wall -Wextra -O2 -fopenmp

all: gauss graph

gauss: gauss.c
	$(CC) $(CFLAGS) -o gauss gauss.c
	

graph: graph.c
	$(CC) $(CFLAGS) -o graph graph.c

clean:
	rm -f gauss graph
