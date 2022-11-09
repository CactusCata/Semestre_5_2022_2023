#include "stack.h"

/**
 * @brief Create a Stack object
 * 
 * @return Stack* 
 */
Stack* createStack() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->size = 0;
    stack->first = NULL;
    return stack;
}

/**
 * @brief Libère la mémoire d'un Stack
 * 
 * @param stack stack ciblé
 */
void freeStack(Stack *stack) {
    freeSElement(stack->first);
    free(stack); // need to remove this if stack is not pointor and he is an array of stack
}

/**
 * @brief Libère la mémoire pour un élément du stack et tous ses suivants
 * 
 * @param sElement 
 */
void freeSElement(SElement *sElement) {
    if (sElement != NULL) {
        freeSElement(sElement->next);
        free(sElement);
    }
}

/**
 * @brief Ajoute un élément dans la pile
 * 
 * @param stack pile cibliée
 * @param sElement élément à ajouter
 */
void pushSElement(Stack *stack, SElement *sElement) {
    SElement *newSecond = stack->first;
    stack->first = sElement;
    sElement->next = newSecond;
}

/**
 * @brief Ajoute un élément dans la pile
 * 
 * @param stack pile cibliée
 * @param int élément à ajouter
 */
void push(Stack *stack, int value) {
    SElement *element = (SElement *) malloc(sizeof(SElement));
    element->next = NULL;
    element->value = value;
    pushSElement(stack, element);
    stack->size++;
}

/**
 * @brief Récupère le dernier élément ajouté
 * 
 * @param stack pile ciblée
 * @return int dernier élément ajouté si la pile n'est pas vide. Sinon renvoie -1
 */
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

/**
 * @brief Renvoie 1 si la pile est vide, 0 sinon
 * 
 * @param stack pile ciblée
 * @return unsigned char 1 si la pile est vide, 0 sinon
 */
unsigned char stackIsEmpty(Stack *stack) {
    return stack->first == NULL;
}

/**
 * @brief Ecrit sur la sortie standard l'état actuel de la pile
 * 
 * @param stack pile ciblée
 */
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
