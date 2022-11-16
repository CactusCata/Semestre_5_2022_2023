CC = g++
CFLAGS = -g -Wall

# build executable
main: main.o oeuvre.o tableau.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.cc
	$(CC) $(CFLAFS) -c $<

oeuvre.o: oeuvre.cc
	$(CC) $(CFLAFS) -c $<

tableau.o: tableau.cc
	$(CC) $(CFLAFS) -c $<