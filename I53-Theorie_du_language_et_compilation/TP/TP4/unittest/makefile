CC= gcc
CFLAGS= -Wall -g
CLIBS_PATH = -I../lib -L../lib
CLIBS_BASICS = -lm
CLIBS = -laf -lutils -lcontainer -lgraphviz -lregex $(CLIBS_BASICS)

# Main app
prog.exe: unitUtils.o utils_unit.o arrayUtils_unit.o vect_unit.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS) $(CLIBS_PATH)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $<

unitUtils.o: unitUtils.c unitUtils.h
	$(CC) $(CFLAGS) -c $<

# Units test
utils_unit.o: utils_unit.c utils_unit.h
	$(CC) $(CFLAGS) -c $<

arrayUtils_unit.o: arrayUtils_unit.c arrayUtils_unit.h
	$(CC) $(CFLAGS) -c $<

vect_unit.o: vect_unit.c vect_unit.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.exe *~ *.o
