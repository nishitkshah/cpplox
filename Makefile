IDIR=includes
CC=g++
CFLAGS=-I $(IDIR)

CDIR=core

OBJ = add.o adder.o

%.o: $(CDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	main

.PHONY: clean

clean:
	rm *.o