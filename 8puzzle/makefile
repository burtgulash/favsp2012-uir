CC = gcc
CCFLAGS = -g -Wall -pedantic -ansi

EXEC = 8puzzle
SRCS = set.c list.c pqueue.c grid.c main.c


$(EXEC) : $(SRCS)
	$(CC) $(CCFLAGS) -o $(EXEC) $^

.PHONY: clean

clean :
	rm $(EXEC)
