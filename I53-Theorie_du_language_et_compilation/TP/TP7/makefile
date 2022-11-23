CC = gcc
CFLAGS = -g -Wall

all: parser

# build executable
parser: parser.o lexer.o ts.o
	$(CC) $(CFLAGS) -o $@ $^ -lfl

# ts
ts.o: ts.c ts.h
	$(CC) $(CFLAGS) -c $<

# parser
parser.o: parser.c
	$(CC) $(CFLAGS) -c $<

parser.c: parser.y
	bison -o $@ -d $<

# Lexer
lexer.o: lexer.c
	$(CC) $(CFLAGS) -c $<

lexer.c: lexer.lex
	flex -o $@ $<

clean:
	rm -f parser.c lexer.c parser
