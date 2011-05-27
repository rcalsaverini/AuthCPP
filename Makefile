CC	= g++
CFLAGS	= -std=gnu++0x -m64 -O3 -Wall  #-g -pg
IFLAGS	= -I/usr/include/igraph
LFLAGS	= -L/usr/local/lib -ligraph -lgsl -lgslcblas -lm 
#FLAGS = -I/usr/include/igraph -L/usr/local/lib -ligraph -lgsl -lgslcblas -lm -m64 -O3 -std=gnu++0x
# -g -pg -Wall -ansi

all: test
fresh: clean test

test: teste.o Graph.o Random.o Agent.o Sim.o
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@

teste.o: Teste.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@

Sim.o: Sim.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@	

Agent.o: Agent.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@	

Graph.o: Graph.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@	

Random.o: Random.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@	

clean: clean-test clean-o clean-temp

clean-test:
	-rm test -rfv

clean-o:
	-rm *.o -rfv

clean-temp:
	-rm *~ -rfv