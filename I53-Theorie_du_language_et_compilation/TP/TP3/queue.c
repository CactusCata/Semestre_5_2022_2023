#include "queue.h"

Queue *createQueue() {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->first = NULL;
    return queue;
}

Element *createElement(lexicalUnitCatch *lexicalUnit) {
    Element *element = (Element *) malloc(sizeof(Element));
    element->value = lexicalUnit;
    element->next = NULL;
    return element;
}

void add(Queue *queue, lexicalUnitCatch *lexicalUnit) {
    Element *e = createElement(lexicalUnit);

    if (queue->first == NULL) {
        queue->first = e;
        return;
    }

    Element* current = queue->first;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = e;
}

lexicalUnitCatch *pop(Queue *queue) {
    Element *element = queue->first;

    if (element == NULL) {
        return NULL;
    }

    lexicalUnitCatch *lexicalUnit = element->value;
    queue->first = element->next;
    free(element);
    return lexicalUnit;
}

void printQueue(Queue *queue) {
    printf("Queue printing...\n");
    Element *current = queue->first;

    while (current != NULL) {
        printf("[%s, %s]\n", current->value->reCategory, current->value->caught);
        current = current->next;
    }
}

void freeQueue(Queue *queue) {
    free(queue->first);
    free(queue);
}


void freeElement(Element *element) {
    if (element != NULL) {
        freeElement(element->next);
        free(element);
    }
}