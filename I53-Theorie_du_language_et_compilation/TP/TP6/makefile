CC = gcc
CFLAGS = -Wall -g
YACC = bison -v -Wconflicts-sr

calc.exe: calc.o
	$(CC) $(CFLAGS) -o $@ $^

calc.o: calc.c
	$(CC) $(CFLAGS) -c $<

calc.c: calc.y
	$(YACC) $^ -o $@

clean:
	rm -f *.exe *.o *.c
