CC=gcc
LDFLAGS=-lcmocka
VFLAGS=`sdl2-config --cflags --libs` -lm

# VISUALIZATION
visualization: visualization.c genFile.c adjlst.h
	$(CC) -o $@ $< $(VFLAGS)
	$(CC) -o genFile genFile.c
plot: visualization.c genFile.c adjlst.h
	./genFile graph
	./visualization graph


# RUN TESTS
check: test_adjlst
	./test_adjlst
.PHONY: check

# COMPILE TESTS
test_adjlst: test_adjlst.c adjlst.h
	$(CC) -o $@ $< $(LDFLAGS)

# CLEAN
clean:
	rm -f *.o test_adjlst
.PHONY: clean