#ifndef ELEMENT_HPP
#define ELEMENT_HPP

typedef struct Element {
    Element *next;
    Serializable *item;
} Element;

#endif