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

run_prog:
	bin/prog

######################################

clean:
	rm *.o bin/*