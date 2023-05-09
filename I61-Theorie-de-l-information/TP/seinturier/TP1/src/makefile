CC = gcc
CFLAGS = -g -Wall
BIN_FOLDER = ../bin

SOURCE_FILES=\
	utils.c

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BIN_FOLDER)/%.o)

EXECUTABLE: ../prog_1.exe ../prog_2.exe

# build executable
../prog_1.exe: $(OBJECT_FILES)
	make -BC tp1
	$(CC) $(CFLAGS) -o $@ $(BIN_FOLDER)/*

../prog_2.exe: $(OBJECT_FILES)
	make -BC tp2
	$(CC) $(CFLAGS) -o $@ $(BIN_FOLDER)/*

$(OBJECT_FILES): $(BIN_FOLDER)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *~  $(BIN_FOLDER)/*.o $(EXECUTABLE)
