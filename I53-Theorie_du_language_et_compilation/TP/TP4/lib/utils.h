#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;

int getNextIntFromLine(char *lineBuffer, unsigned int *cursor);

int *getAllIntInLine(char *line, int sizeArray);

// Append text in another text at the end (from the index indexStartToWrite)
// The index indexStartToWrite is update at the end of this function
void appendText(char *base, char *toAdd, int *indexStartToWrite);

void writeNTimes(char *text, int *startWrittingIndex, char c, int times);

void throwMallocErrorIfTrue(bool condition);

#endif
