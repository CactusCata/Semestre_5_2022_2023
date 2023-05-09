CC = gcc
CFLAGS = -g -Wall
BIN_FOLDER = ../../bin

SOURCE_FILES =\
	main.c\
	matrix.c\
	vector.c\

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BIN_FOLDER)/%.o)

all:$(OBJECT_FILES)

$(OBJECT_FILES): $(BIN_FOLDER)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
