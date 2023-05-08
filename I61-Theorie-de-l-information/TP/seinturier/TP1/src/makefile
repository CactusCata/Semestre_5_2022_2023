CC = gcc
CFLAGS = -g -Wall
BIN_FOLDER = ../bin

SOURCE_FILES =\
	main.c\
	matrix.c\
	utils.c\
	vector.c

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BIN_FOLDER)/%.o)

EXECUTABLE: ../prog.exe

# build executable
../prog.exe: $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJECT_FILES): $(BIN_FOLDER)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *~  $(BIN_FOLDER)/*.o $(EXECUTABLE)
	