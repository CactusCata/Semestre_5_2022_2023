#include "unitUtils.h"

static char *lastFunctionName;
static char *lastFunctionParameters;

void initUnitTest() {
    lastFunctionParameters = (char *) malloc(sizeof(char) * 128);
}

void endUnitTest() {
    free(lastFunctionParameters);
}

void intEqual(int obtainedValue, int expectedValue) {
    if (expectedValue != obtainedValue) {
        colorRed();
        throwError();
        printf("Expected value: %d\n", expectedValue);
        printf("Obtained value: %d\n", obtainedValue);
        colorReset();
        exit(1);
    } else {
        testPassed();
    }
}

void charEqual(char obtainedValue, char expectedValue) {
    if (expectedValue != obtainedValue) {
        colorRed();
        throwError();
        printf("Expected value: '%c'\n", expectedValue);
        printf("Obtained value: '%c'\n", obtainedValue);
        colorReset();
        exit(1);
    } else {
        testPassed();
    }
}

void boolEqual(bool obtainedValue, bool excptectedValue) {
    if (obtainedValue != excptectedValue) {
        colorRed();
        throwError();
        printf("Expected value: '%s'\n", excptectedValue ? "true" : "false");
        printf("Obtained value: '%s'\n", obtainedValue ? "true" : "false");
        colorReset();
        exit(1);
    } else {
        testPassed();
    }
}

void intArrayEqual(int *obtainedValue, int *expectedValue, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        if (expectedValue[i] != obtainedValue[i]) {
            colorRed();
            throwError();
            printf("Expected value: ");
            printIntArray(expectedValue, arraySize);
            printf("\n");
            printf("Obtained value: ");
            printIntArray(obtainedValue, arraySize);
            printf("\n");
            colorReset();
            exit(1);
        }
    }
    testPassed();
}

void charArrayEqual(char *obtainedValue, char *expectedValue, int size) {
    for (int i = 0; i < size; i++) {
        if (expectedValue[i] != obtainedValue[i]) {
            colorRed();
            throwError();
            printf("Expected value: ");
            printCharArray(expectedValue, size);
            printf("\n");
            printf("Obtained value: ");
            printCharArray(obtainedValue, size);
            printf("\n");
            colorReset();
            exit(1);
        }
    }

    testPassed();
}

void stringEqual(char *obtainedValue, char *expectedValue) {
    if (strlen(expectedValue) != strlen(obtainedValue)) {
        colorRed();
        throwError();
        printf("Expected value: \"%s\"\n", expectedValue);
        printf("Obtained value: \"%s\"\n", obtainedValue);
        colorReset();
        exit(1);
    }

    for (int i = 0; expectedValue[i] != '\0'; i++) {
        if (expectedValue[i] != obtainedValue[i]) {
            colorRed();
            throwError();
            printf("Expected value: \"%s\"\n", expectedValue);
            printf("Obtained value: \"%s\"\n", obtainedValue);
            colorReset();
            exit(1);
        }
    }

    testPassed();
}

void appendTextUnit(char *base, char *toAdd, int *indexStartToWrite) {
  int i = 0;
  for (; toAdd[i] != '\0'; i++) {
    base[*indexStartToWrite + i] = toAdd[i];
  }
  base[*indexStartToWrite + i] = '\0';
  (*indexStartToWrite) += i;
}

char *serializeIntArray(int *array, int size) {
  char *text = (char *) malloc(sizeof(char) * 128);
  int textCursorW = 0;
  text[textCursorW++] = '{';
  if (size > 0) {
    char numberBuffer[20];
    for (size_t i = 0; i < size - 1; i++) {
      sprintf(numberBuffer, "%d, ", array[i]);
      appendTextUnit(text, numberBuffer, &textCursorW);
    }
    sprintf(numberBuffer, "%d", array[size - 1]);
    appendTextUnit(text, numberBuffer, &textCursorW);
  }
  text[textCursorW++] = '}';
  text[textCursorW++] = '\0';
  return text;
}

void printIntArray(int *array, int size) {
    char *arraySerialized = serializeIntArray(array, size);
    printf("%s", arraySerialized);
    free(arraySerialized);
}

void printCharArray(char *array, int size) {
    printf("[");
    if (size > 0) {
        for (int i = 0; i < size - 1; i++) {
            printf("'%c', ", array[i]);
        }
        printf("'%c'", array[size - 1]);
    }
    printf("]");
}

void setTestFunctionName(char *functionName) {
    lastFunctionName = functionName;
}

void testPassed() {
    colorGreen();
    fprintf(stdout, "Test passed for function %s(", lastFunctionName);
    fprintf(stdout, "%s", lastFunctionParameters);
    fprintf(stdout, ")\n");
    colorReset();
}

void throwError() {
    fprintf(stdout, "Function %s(", lastFunctionName);
    fprintf(stdout, "%s", lastFunctionParameters);
    fprintf(stdout, ") do not return right value: \n");
    endUnitTest();
}

#pragma GCC diagnostic ignored "-Wvarargs"
void setTestFunctionParameters(char *format, ...) {
    char *updatedFormat = addQuoteOnStringsAndCharFormat(format);
    va_list args;
    va_start(args, updatedFormat);
    vsprintf(lastFunctionParameters, updatedFormat, args);
    va_end(args);
    free(updatedFormat);
}

char *addQuoteOnStringsAndCharFormat(char *format) {
    char *newFormat = (char *) malloc(sizeof(char) * 256);

    int indexFormat = 0;
    int indexNewFormat = 0;

    while (format[indexFormat] != '\0') {
        if (format[indexFormat] == '%') {
            if (format[indexFormat + 1] == 's') {
                newFormat[indexNewFormat++] = '\"';
                newFormat[indexNewFormat++] = '%';
                newFormat[indexNewFormat++] = 's';
                newFormat[indexNewFormat++] = '\"';
                indexFormat += 2;
            } else if (format[indexFormat + 1] == 'c') {
                newFormat[indexNewFormat++] = '\'';
                newFormat[indexNewFormat++] = '%';
                newFormat[indexNewFormat++] = 'c';
                newFormat[indexNewFormat++] = '\'';
                indexFormat += 2;
            } else {
                newFormat[indexNewFormat++] = format[indexFormat++];
            }
        } else if (format[indexFormat] == ' ') {
                newFormat[indexNewFormat++] = ',';
                newFormat[indexNewFormat++] = format[indexFormat++];
        } else {
            newFormat[indexNewFormat++] = format[indexFormat++];
        }
    }
    newFormat[indexNewFormat++] = '\0';
    return newFormat;
}


void colorRed() {
    printf("\033[0;31m");
}

void colorGreen() {
    printf("\033[0;32m");
}

void colorReset() {
    printf("\033[0;0m");
}