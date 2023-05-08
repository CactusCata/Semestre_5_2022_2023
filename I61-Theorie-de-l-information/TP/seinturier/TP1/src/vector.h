#ifndef VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

typedef int* Vec;

// Supprime un vecteur en mémoire
void vec_free(Vec v);

// Crée un vecteur vide de taille n
Vec vec_create(uint n);

// Copie un vecteur de taille n
Vec vec_copy(Vec v, uint n);

// Affiche le contenue d'un vecteur de taille n dans la console
void vec_print(Vec v, uint n);

// Convertie un entier en vecteur de taille n
Vec int_to_vec(uint x, uint n);

// Convertie un vecteur de taille n en entier
int vec_to_int(Vec v, uint n);

// Renvoie le nombre de bits de poids fort consécutifs à 0
int vec_get_unused_bits(Vec v, uint n);

// Renvoie l'ensemble des 2^k vecteurs binaires possibles de taille k
Vec* vec_possibilities(uint k);

// Renvoie le poids d'un vecteur binaire
uint vec_hamming_weight(Vec v, uint n);

// Renvoie la différence entre deux vecteurs u et v de taille n
Vec vec_diff(Vec u, Vec v, uint n);

// Renvoie la distance de Hamming entre deux vecteurs
// (la distance de Hamming est le nombre de composantes différentes entre 2 vecteurs binaires)
uint vec_hamming_distance(Vec u, Vec v, uint n);

uint dist_min(Vec* vecteurs, uint n, uint nb_vect);

uint capacite_decodage(Vec* vecteurs, uint n, uint nb_vect);

// Inverse le bit b du vecteur v de taille n
Vec vec_noised(Vec v, uint n, uint b);

#endif