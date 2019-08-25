IDIR=includes
CC=g++
CFLAGS=-I $(IDIR) -g

CXXDIR=lox
ASTDIR=lox/ast

OBJ = cpplox.o lox.o scanner.o token.o expr.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: $(CXXDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: $(ASTDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

lox: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm *.o