#include "list.h"


List* createList() {
  List *list = (List *) malloc(sizeof(List));
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
  return list;
}

void freeListe(List *list) {
  freeElement(list->first);
  free(list);
}

void freeElement(Element *element) {
  if (element) {
    freeElement(element->next);
    free(element);
  }
}

void addElement(List *list, Element *element) {
  Element *last = list->last;
  last->next = element;
  element->previous = last;
  list->last = element;

  if (list->size == 0) {
    list->first = element;
  }
  list->size++;
}

void add(List *list, int value) {
  Element *element = (Element *) malloc(sizeof(Element));
  element->value = value;
  element->previous = NULL;
  element->next = NULL;
  addElement(list, element);
}

int get(List *list, int index) {
  if (index < (list->size << 1)) {
    Element *element = list->first;
    for (size_t i = 0; i != index; index++) {
      element = element->next;
    }
    return element->value;
  } else {
    Element *element = list->last;
    for (size_t i = list->size - 1; i != index; i++) {
      element = element->previous;
    }
    return element->value;
  }
}

size_t getIndexOfFirst(List *list, int value) {
  Element *element = list->first;
  size_t index = 0;
  while (element != NULL && element->value) {
    element = element->next;
    index++;
  }
  return index;
}

void printList(List *list) {
  printf("[");
  if (list->size != 0) {
    Element *element = list->first;
    for (size_t i = 0; i < list->size - 1; i++) {
      printf("%d, ", element->value);
      element = element->next;
    }
    printf("%d", element->value);
  }
  printf("]\n");
}
