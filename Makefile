SHELL := /bin/bash
CC = g++-4.4
FLAGS = -I/usr/include/igraph -L/usr/local/lib -ligraph -lgsl -lgslcblas -lm -m64 -O3 -ansi
# -g -pg -Wall -ansi

all: test

test: teste.o Graph.o Random.o Agent.o Sim.o
	$(CC) $(FLAGS) $^ -o $@

teste.o: Teste.cpp
	$(CC) $(FLAGS) -c $^ -o $@

Sim.o: Sim.cpp
	$(CC) $(FLAGS) -c $^ -o $@	

Sim2.o: Sim2.cpp
	$(CC) $(FLAGS) -c $^ -o $@	

Agent.o: Agent.cpp
	$(CC) $(FLAGS) -c $^ -o $@	

Graph.o: Graph.cpp
	$(CC) $(FLAGS) -c $^ -o $@	

Random.o: Random.cpp
	$(CC) $(FLAGS) -c $^ -o $@	

clean-all: 
	-rm *.o
	-rm *~
	-rm test

clean-test:
	-rm test

clean-o:
	-rm *.o

clean-bin:
	-rm run

clean:
	-rm *~