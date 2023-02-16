#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "ts.h"

extern FILE *ramFile;
extern ts table;

void initMemoryArrayCursor();

void increaseMemoryVariableSize();

void creerTableau(char *identificateur);

void LOAD_VALUE(int n);

void LOAD_MEM(int memoryLine);

void LOAD_VARIABLE(char *identificateur);

void JUMP(int codeLine);

void JUMZ(int codeLine);

void JUMG(int codeLine);

void JUML(int codeLine);

void STORE(int memoryLine);

void STORE_VARIABLE(char *identificateur);

void ADD(int memoryLine);

void SUB(int memoryLine);

void MUL(int memoryLine);

void DIVI(int memoryLine);

void MOD(int memoryLine);

void MUL_VALUE(int value);

void WRITE();

void READ();

void decrementStackCursor(int n);

void resetStackCursor();

void increaseCodeLine();

int getCurrentLineCode();

void setStackCursor(int n);

int getCurrentStackCursor();

int getID(char *identificateur);

int addID(char *identificateur);

void freeTable();

#endif