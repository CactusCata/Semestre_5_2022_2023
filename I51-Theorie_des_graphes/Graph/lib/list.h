#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LLElement {
  struct LLElement *next;
  struct LLElement *previous;
  int value;
} LLElement;

typedef struct List {
  size_t size;
  LLElement *first;
  LLElement *last;
} List;

List* createList();

void freeListe(List *list);

void freeLLElement(LLElement *LLElement);

void addLLElement(List *list, LLElement *LLElement);

void add(List *list, int value);

int get(List *list, int index);

size_t getIndexOfFirst(List *list, int value);
// renvoie l'indice du premier LLElement qui vaut value dans la liste

void printList(List *list);

#endif
