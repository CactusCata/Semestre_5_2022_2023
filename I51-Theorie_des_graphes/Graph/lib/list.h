#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
  struct Element *next;
  struct Element *previous;
  int value;
} Element;

typedef struct List {
  size_t size;
  Element *first;
  Element *last;
} List;

List* createList();

void freeListe(List *list);

void freeElement(Element *element);

void addElement(List *list, Element *element);

void add(List *list, int value);

int get(List *list, int index);

size_t getIndexOfFirst(List *list, int value);
// renvoie l'indice du premier element qui vaut value dans la liste

void printList(List *list);

#endif
