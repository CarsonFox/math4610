HDIR = ./include
ODIR = ./lib
CC = gcc
CFLAGS = -I$(HDIR) -Wall -Wextra -std=c11

DEPS = $(HDIR)/rootfinding.h

_OBJ = newton.o secant.o bisection.o functional_iter.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.DEFAULT_GOAL = main

%.h: ;

lib/%.o: $(ODIR)/$@.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lib/rootfinding.a: $(OBJ) $(DEPS)
	ar rcv $(ODIR)/rootfinding.a $(OBJ)
	ranlib $(ODIR)/rootfinding.a

main: main.c lib/rootfinding.a $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(ODIR)/rootfinding.a main
