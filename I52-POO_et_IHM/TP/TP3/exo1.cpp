#include "exo1.hpp"

void zLocalFunction() {
    Complexe zLocal(4, 5);
}

void zParamValue(Complexe z) {

}

void zParamRef(Complexe &z) {

}

Complexe zReturnCopy() {
  return Complexe(5, 6);
}

Complexe& zReturnRef(Complexe &z) {
  return z;
}
