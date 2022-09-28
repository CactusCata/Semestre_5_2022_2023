#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "serializable.hpp"
#include "element.hpp"

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
        bool isEmpty();

        Serializable *pop();

};


#endif
