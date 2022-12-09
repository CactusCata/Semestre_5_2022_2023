CC = gcc
CFLAGS = -g -Wall
BIN_FOLDER = ../bin
CLIBS_PATH = -I$(BIN_FOLDER) -L$(BIN_FOLDER)
CLIBS_BASICS = -lm
CLIBS = $(CLIBS_BASICS)

SRC_FILES =\
	acm.c\
	graphDis.c\
	graphListAdj.c\
	graphMatAdj.c\
	graphAcm.c\
	graphTypeConvertor.c\
	graphUtils.c\
	list.c\
	mathUtils.c\
	stack.c\
	utils.c\
	partition.c\
	clique.c


OBJECT_FILES = $(SRC_FILES:%.c=$(BIN_FOLDER)/%.o)

prog.exe: main.o
	$(CC) $(CFLAGS) -o ../$@ $^ $(OBJECT_FILES) $(CLIBS_PATH) $(CLIBS)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c $<

partition.png: partition.dat partition.plot
	gnuplot partition.plot

clean:
	rm -f ../*.exe *.o
