CC = gcc
CFLAGS = -g -Wall
BIN_FOLDER = ../bin

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

all: $(OBJECT_FILES)

test_stack.exe: stack.o test_stack.c
	$(CC) $(CFLAGS) -o $@ $^


$(OBJECT_FILES): $(BIN_FOLDER)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Cleaner
clean:
	rm -f *.exe *.o *.a $(BIN_FOLDER)/*.o
