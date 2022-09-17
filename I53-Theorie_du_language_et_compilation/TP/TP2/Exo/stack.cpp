#include "stack.hpp"

Stack::Stack() {
    first = nullptr;
    size = 0;
}

void Stack::print() {
    std::cout << '(';
    if (first != nullptr) {
        std::cout << first->value;
        Element *e = first->next;
        while (e != nullptr) {
            std::cout << ", " << e->value;
            e = e->next;
        }
    }
    std::cout << ')' << std::endl;
}

Element* Stack::newElement(char value) {
    Element* e = new Element;
    e->next = nullptr;
    e->value = value;
    return e;
}

bool Stack::push(Element* e) {
    if (e == nullptr) {
        return false;
    }

    e->next = first;
    first = e;
    size++;
    return true;
}

bool Stack::push(char value) {
    Element *e = newElement(value);
    bool successfullyPush = push(e);
    
    if (!successfullyPush) {
        delete e;
    }

    return successfullyPush;
}

char Stack::pop() {

    Element* e = first;
    if (e != nullptr) {
        first = e->next;
        size--;
        char c = e->value;
        delete e;
        return c;
    }
    
    size--;
    return '?';
}