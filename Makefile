IDIR=includes
CC=g++
CFLAGS=-I $(IDIR)

CDIR=lox

OBJ = cpplox.o lox.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: $(CDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

lox: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm *.o