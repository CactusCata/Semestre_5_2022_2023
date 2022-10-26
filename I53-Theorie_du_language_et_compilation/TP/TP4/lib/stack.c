#include "stack.h"

Stack* createStack() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->size = 0;
    stack->first = NULL;
    return stack;
}

void freeStack(Stack *stack) {
    freeSElement(stack->first);
    //free(stack); // need to remove this if stack is not pointor
    // and he is an array of stack
}

void freeSElement(SElement *sElement) {
    if (sElement != NULL) {
        freeSElement(sElement->next);
        free(sElement);
    }
}

void pushSElement(Stack *stack, SElement *sElement) {
    SElement *newSecond = stack->first;
    stack->first = sElement;
    sElement->next = newSecond;
}

void push(Stack *stack, int value) {
    SElement *element = (SElement *) malloc(sizeof(SElement));
    element->next = NULL;
    element->value = value;
    pushSElement(stack, element);
    stack->size++;
}

int pop(Stack *stack) {
    if (stackIsEmpty(stack)) {
        return -1;
    }

    SElement *oldSecond = stack->first->next;
    int firstValue = stack->first->value;
    free(stack->first);
    stack->first = oldSecond;
    stack->size--;
    return firstValue;
}

unsigned char stackIsEmpty(Stack *stack) {
    return stack->first == NULL;
}

void printStack(Stack *stack) {
    printf("[");
    if (stack->size != 0) {
        SElement *sElement = stack->first;
        for (size_t i = 0; i < stack->size - 1; i++) {
            printf("%d, ", sElement->value);
            sElement = sElement->next;
        }
        printf("%d", sElement->value);
    }
    printf("]\n");
}
