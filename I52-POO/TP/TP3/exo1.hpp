#ifndef EXO_1_HPP
#define EXO_1_HPP

#include <cstddef>
#include "complexe.hpp"

void zLocalFunction();
void zParamValue(Complexe z);
void zParamRef(Complexe &z);
Complexe zReturnCopy();
Complexe& zReturnRef(Complexe &z);

#endif
