CC=gcc
LDFLAGS=-lcmocka
VFLAGS=`sdl2-config --cflags --libs` -lm

# VISUALIZATION
visualization: visualization.c genFile.c adjlst.c adjlst.h
	$(CC) -o visualization visualization.c adjlst.c $(VFLAGS)
	$(CC) -o genFile genFile.c adjlst.c
plot: visualization.c genFile.c adjlst.h
	./genFile graph
	./visualization graph

# CORE FILES
adjlst.o: adjlst.c adjlst.h
	$(CC) -c $<
subgraph.o: subgraph.c subgraph.h
	$(CC) -c $<

# RUN TESTS
check: test_adjlst test_subgraph
	./test_adjlst
	./test_subgraph
.PHONY: check

# COMPILE TESTS
test_adjlst: TESTS/test_adjlst.c adjlst.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_subgraph: TESTS/test_subgraph.c subgraph.o adjlst.o
	$(CC) -o $@ $^ $(LDFLAGS)

# CLEAN
clean:
	rm -f *.o
	rm -f test_adjlst test_subgraph
	rm -f visualization genFile graph
	rm -f a.out
.PHONY: clean