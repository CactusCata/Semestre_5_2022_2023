#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

typedef struct Element {
    Element *next;
    char value;
} Element;

class Stack {

    private:
        unsigned int size;
        Element* first;

        Element* newElement(char value);
        bool push(Element* e);

    public:
        Stack();
        void print();
        bool push(char c);

        char pop();

};


#endif
