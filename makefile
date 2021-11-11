CC=gcc
LDFLAGS=-lcmocka

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