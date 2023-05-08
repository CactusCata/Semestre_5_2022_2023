#ifndef UTILS_H

#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;

// Renvoie la valeur 2^n
int pow2(uint n);

// Renvoie le poids de Hamming d'un entier
uint get_hamming_weight(uint n);

#endif