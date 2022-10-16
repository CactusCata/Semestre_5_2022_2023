#include "stack.h"

int main(int argc, char *argv[]) {
    Stack *stack = createStack();

    printStack(stack);

    printf("Stack top value: %d\n", pop(stack));

    push(stack, 2);
    push(stack, 8);
    push(stack, 14);

    printStack(stack);

    printf("Stack top value: %d\n", pop(stack));
    printf("Stack top value: %d\n", pop(stack));
    printf("Stack top value: %d\n", pop(stack));
    printf("Stack top value: %d\n", pop(stack));
}