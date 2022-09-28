HDIR = ./include
CC = gcc
CFLAGS = -I$(HDIR) -Wall -Wextra

ODIR = ./lib

_DEPS = rootfinding.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = newton.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.DEFAULT_GOAL = main

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/rootfinding.ar: $(OBJ)
	ar rcv $(ODIR)/rootfinding.a $(OBJ)
	ranlib $(ODIR)/rootfinding.a

main: main.c $(ODIR)/rootfinding.a
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(ODIR)/rootfinding.ar main
