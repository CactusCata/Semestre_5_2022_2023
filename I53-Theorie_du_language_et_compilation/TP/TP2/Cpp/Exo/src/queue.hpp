#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include "serializable.hpp"
#include "element.hpp"

class Queue {

    private:
        unsigned int size;
        Element* first;

        Element* newElement(Serializable *item);
        bool add(Element* e);

    public:
        Queue();
        void print();
        bool add(Serializable *item);
        bool isEmpty();

        Serializable *get();


};

#endif