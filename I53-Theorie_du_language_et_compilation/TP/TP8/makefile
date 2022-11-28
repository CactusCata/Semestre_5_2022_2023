CC = gcc
CFLAGS = -g -Wall

SOURCE_FILES =\
	asa.c\
	parser.c\
	lexer.c\
	ts.c

OBJECT_FILES = $(SOURCE_FILES:%.c=%.o)

all: prog.exe

# build executable
prog.exe: $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

$(OBJECT_FILES): %.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# parser
parser.c: parser.y
	bison -o $@ -d $<

# Lexer
lexer.c: lexer.lex
	flex -o $@ $<

clean:
	rm -f parser.c parser.h lexer.c prog.exe *.o
