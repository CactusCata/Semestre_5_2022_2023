#include "stack.hpp"

Stack::Stack() {
    first = nullptr;
    size = 0;
}

void Stack::print() {
    std::cout << '(';
    if (first != nullptr) {
        std::cout << first->item->serialize();
        Element *e = first->next;
        while (e != nullptr) {
            std::cout << ", " << e->item->serialize();
            e = e->next;
        }
    }
    std::cout << ')' << std::endl;
}

Element* Stack::newElement(Serializable *item) {
    Element* e = new Element;
    e->next = nullptr;
    e->item = item;
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

bool Stack::push(Serializable *item) {
    Element *e = newElement(item);
    bool successfullyPush = push(e);
    
    if (!successfullyPush) {
        delete e;
    }

    return successfullyPush;
}

Serializable *Stack::pop() {

    Element* e = first;
    if (!isEmpty()) {
        first = e->next;
        size--;
        Serializable *c = e->item;
        delete e;
        return c;
    }
    
    size--;
    return nullptr;
}

bool Stack::isEmpty() {
    return first == nullptr;
}