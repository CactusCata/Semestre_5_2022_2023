#include "queue.hpp"

Queue::Queue() {
    first = nullptr;
    size = 0;
}

void Queue::print() {
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

Element* Queue::newElement(Serializable *item) {
    Element* e = new Element;
    e->next = nullptr;
    e->item = item;
    return e;
}

bool Queue::add(Element* e) {
    if (e == nullptr) {
        return false;
    }

    if (isEmpty()) {
        first = e;
    } else {
        Element *current = first;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = e;
    }

    size++;
    return true;
}

bool Queue::add(Serializable *item) {
    Element *e = newElement(item);
    bool successfullyPush = add(e);
    
    if (!successfullyPush) {
        delete e;
    }

    return successfullyPush;
}

bool Queue::isEmpty() {
    return first == nullptr;
}

Serializable *Queue::get() {

    Element* e = first;
    if (e != nullptr) {
        first = e->next;
        size--;
        Serializable *c = e->item;
        delete e;
        return c;
    }
    
    size--;
    return nullptr;
}