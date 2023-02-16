CC = gcc
CFLAGS = -g -Wall
BIN_FOLDER = ../bin

SOURCE_FILES =\
	asa_utils.c\
	asa_codegen.c\
	asa_node_creator.c\
	parser.c\
	lexer.c\
	ts.c\
	instruction.c

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BIN_FOLDER)/%.o)

all: ../prog.exe

# build executable
../prog.exe: $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

$(OBJECT_FILES): $(BIN_FOLDER)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# parser
parser.c: parser.y
	bison -o $@ -d $< -Wconflicts-sr

# Lexer
lexer.c: lexer.lex
	flex -o $@ $<

clean:
	rm -f parser.c parser.h lexer.c $(BIN_FOLDER)/*.o
