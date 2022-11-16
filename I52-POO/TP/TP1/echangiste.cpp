#include "echangiste.hpp"
#include "complexe.hpp"

void permuter(int &a, int &b) {
    int &cached = a;
    a = b;
    b = cached;
}


void permuter(Complexe& c1, Complexe& c2) {
    Complexe cached = c1;
    c1 = c2;
    c2 = cached;
}