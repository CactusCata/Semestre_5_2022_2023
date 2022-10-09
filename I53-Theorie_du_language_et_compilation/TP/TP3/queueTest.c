#include "queue.h"
#include "unilex.h"

int main(int argc, char *argv[]) {
    lexicalUnitCatch lu1 = {.reCategory = "sep", .caught = "prout"};
    lexicalUnitCatch lu2 = {.reCategory = "sep2", .caught = "prout2"};
    lexicalUnitCatch lu3 = {.reCategory = "sep3", .caught = "prout3"};
    
    Queue *queue = createQueue();
    add(queue, &lu1);
    add(queue, &lu2);

    printQueue(queue);

    lexicalUnitCatch *current = pop(queue);

    printf("%s %s\n", current->reCategory, current->caught);

    printQueue(queue);

}