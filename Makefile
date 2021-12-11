######################################
############# Variables ##############
######################################

# COMPILER
CC=g++
CFLAGS=-O3

# DIRECTORIES
INC=-I ./include

# OBJECT FILES
OBJ=graph.o main.o

# TESTS
TESTS=graphtests

######################################
############## Makefile ##############
######################################

prog: $(OBJ)
	$(CC) -o bin/$@ $(CFLAGS) $(OBJ) 

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c $(INC) $<

graph.o: src/graph.cpp
	$(CC) $(CFLAGS) -c $(INC) $<

######################################
################ Runs ################
######################################

runprog:
	bin/prog

check: $(TESTS)
	bin/graphtests


######################################
############### Tests ###############
######################################

graphtests: tests/graph_tests.cpp graph.o
	$(CC) -o bin/$@ $(INC) graph.o $<

######################################

clean:
	rm *.o bin/*