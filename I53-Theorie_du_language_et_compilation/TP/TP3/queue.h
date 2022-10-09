#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "unilex.h"
#include "stdio.h"

typedef struct Element {
    lexicalUnitCatch *value;
    struct Element *next;
} Element;

typedef struct {
    Element *first;
} Queue;

Queue *createQueue();

Element *createElement(lexicalUnitCatch *lexicalUnit);

void add(Queue *queue, lexicalUnitCatch *lexicalUnit);

lexicalUnitCatch *pop();

void printQueue(Queue *queue);

void freeQueue(Queue *queue);

void freeElement(Element *element);

#endif