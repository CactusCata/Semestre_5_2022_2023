#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct SElement {
  struct SElement *next;
  int value;
} SElement;

typedef struct Stack {
  size_t size;
  SElement *first;
} Stack;

Stack* createStack();

void freeStack(Stack *stack);

void freeSElement(SElement *sElement);

void pushSElement(Stack *stack, SElement *sElement);

void push(Stack *stack, int value);

int pop(Stack *stack);

unsigned char stackIsEmpty(Stack *stack);

void printStack(Stack *stack);

#endif