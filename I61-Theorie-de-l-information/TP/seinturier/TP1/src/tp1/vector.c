#include "vector.h"

void vec_free(Vec v) {
    free(v);
}

Vec vec_create(uint n) {
    Vec empty_vec = (Vec) calloc(sizeof(int), n);
    return empty_vec;
}

Vec vec_copy(Vec v, uint n) {
    Vec new_vec = vec_create(n);
    for (uint i = 0; i < n; i++) {
        if (v[i]) {
            new_vec[i] = 1;
        }
    }
    return new_vec;
}

void vec_print(Vec v, uint n) {
    printf("(");

    if (n != 0) {
        for (int i = 0; i < n - 1; i++) {
            printf("%d,", v[i]);
        }
        printf("%d", v[n - 1]);
    }
    printf(")\n");
}

Vec int_to_vec(uint x, uint n) {
    if (get_hamming_weight(x) > n) {
        return NULL;
    }

    Vec v = vec_create(n);
    for (uint i = 0; x; i++) {
        v[i] = x & 1;
        x >>= 1;
    }

    return v;
}

int vec_get_unused_bits(Vec v, uint n) {
    for (int i = n - 1; i >= 0; i--) {
        if (v[i]) {
            return n - i - 1;
        }
    }
    return n;
}

int vec_to_int(Vec v, uint n) {
    if (!n) {
        return -1;
    }

    uint unused_bits = vec_get_unused_bits(v, n);
    uint sum = 0;
    int i = n - unused_bits - 1;
    for (; i >= 0; i--) {
        sum <<= 1;
        sum |= v[i];
    }
    return sum;
}

Vec* vec_possibilities(uint k) {
    if (k == 0) {
        return NULL;
    }

    Vec *mots = (Vec *) malloc(sizeof(Vec) * (1 << k));
    for (uint i = 0; i <= (1 << k) - 1; i++) {
        mots[i] = int_to_vec(i, k);
    }
    return mots;
}

uint vec_hamming_weight(Vec v, uint n) {
    if (n == 0) {
        return 0;
    }

    uint hamming_weight = 0;
    for (uint i = 0; i < n; i++) {
        if (v[i]) {
            hamming_weight++;
        }
    }
    return hamming_weight;
}

Vec vec_diff(Vec u, Vec v, uint n) {
    if (u == NULL || v == NULL || n == 0) {
        return NULL;
    }

    Vec d = vec_create(n);
    for (uint i = 0; i < n; i++) {
        if (u[i] ^ v[i]) {
            d[i] = 1;
        }
    }
    return d;
}

uint vec_hamming_distance(Vec u, Vec v, uint n) {
    if (u == NULL || v == NULL || n == 0) {
        return 0;
    }

    uint count = 0;
    for (uint i = 0; i < n; i++) {
        if (u[i] ^ v[i]) {
            count++;
        }
    }
    return count;
}


uint dist_min(Vec* vecteurs, uint n, uint nb_vect) {
    uint min_distance = vec_hamming_distance(vecteurs[0], vecteurs[1], n);
    for (uint start = 0; start < nb_vect + 1; start++) {
        for (uint i = start + 1; i < nb_vect; i++) {
            uint distance_hamming = vec_hamming_distance(vecteurs[start], vecteurs[i], n);
            if (distance_hamming < min_distance) {
                min_distance = distance_hamming;
            }
        }
    }
    return min_distance;
}

uint capacite_decodage(Vec* vecteurs, uint n, uint nb_vect) {
    uint min_distance = dist_min(vecteurs, n, nb_vect);
    return (min_distance - 1) >> 1;
}

Vec vec_noised(Vec v, uint n, uint b) {
    Vec v_noised = vec_copy(v, n);
    v_noised[b] = !v_noised[b];
    return v_noised;
}
