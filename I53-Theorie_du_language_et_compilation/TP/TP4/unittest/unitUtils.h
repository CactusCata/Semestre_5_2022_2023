#ifndef UNIT_UTILS_H
#define UNIT_UTILS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

void initUnitTest();

void endUnitTest();

void intEqual(int obtainedValue, int expectedValue);

void charEqual(char obtainedValue, char expectedValue);

void boolEqual(bool obtainedValue, bool excptectedValue);

void intArrayEqual(int *obtainedValue, int *expectedValue, int arraySize);

void charArrayEqual(char *obtainedValue, char *expectedValue, int size);

void stringEqual(char *obtainedValue, char *expectedValue);

void printIntArray(int *array, int size);

void printCharArray(char *array, int size);

void appendTextUnit(char *base, char *toAdd, int *indexStartToWrite);

char *serializeIntArray(int *array, int size);

void setTestFunctionName(char *functionName);

void testPassed();

void throwError();

void setTestFunctionParameters(char *format, ...);

char *addQuoteOnStringsAndCharFormat(char *format);

void colorRed();

void colorGreen();

void colorReset();

#endif