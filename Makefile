######################################
############# Variables ##############
######################################

# COMPILER
CC=g++
CFLAGS=-O3 -std=c++17
sdllib=`sdl2-config --cflags --libs`

# DIRECTORIES
INC=-I ./include

# OBJECT FILES
OBJ=graph.o main.o visualisation.o

# TESTS
TESTS=graphtests

######################################
############## Makefile ##############
######################################

prog: $(OBJ)
	$(CC) -o bin/$@ $(CFLAGS) $(OBJ) $(sdllib)

main.o: src/main.cpp
	$(CC) $(CFLAGS) -c $(INC) $< $(sdllib)

graph.o: src/graph.cpp
	$(CC) $(CFLAGS) -c $(INC) $<

visualisation.o: src/visualisation.cpp
	$(CC) $(CFLAGS) -c $(INC) $< $(sdllib) -lm

######################################
################ Runs ################
######################################

run:
	bin/prog

check: $(TESTS)
	bin/graphtests


######################################
############### Tests ###############
######################################

graphtests: tests/graph_tests.cpp graph.o visualisation.o
	$(CC) -o bin/$@ $(INC) graph.o visualisation.o $< $(sdllib) -lm

######################################

clean:
	rm *.o bin/* *.dat
