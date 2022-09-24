#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "serializable.hpp"

typedef struct Element {
    Element *next;
    Serializable *item;
} Element;

class Stack {

    private:
        unsigned int size;
        Element* first;

        Element* newElement(Serializable *item);
        bool push(Element* e);

    public:
        Stack();
        void print();
        bool push(Serializable *item);

        Serializable *pop();

};


#endif
