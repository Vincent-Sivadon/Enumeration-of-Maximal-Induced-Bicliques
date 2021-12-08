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


# RUN TESTS
check: test_adjlst
	./test_adjlst
.PHONY: check

# COMPILE TESTS
test_adjlst: test_adjlst.c adjlst.c
	$(CC) -o $@ $^ $(LDFLAGS)


# CLEAN
clean:
	rm -f *.o test_adjlst visualization genFile graph
.PHONY: clean