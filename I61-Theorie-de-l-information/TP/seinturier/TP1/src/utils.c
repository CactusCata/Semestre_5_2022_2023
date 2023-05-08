#include "utils.h"

int pow2(uint n) {
    return 1 << n;
}

uint get_hamming_weight(uint n) {
    uint weight = 0;
    while (n) {
        weight++;
        n &= n - 1;
    }
    return weight;
}