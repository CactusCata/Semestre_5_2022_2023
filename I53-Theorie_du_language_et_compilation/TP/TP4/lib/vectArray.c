#include "vectArray.h"

/**
 * @brief Crée un tableau de vecteur 
 * 
 * @return VectArray* tableau de vecteur
 */
VectArray *createVectArray() {
    VectArray *vectArray = (VectArray *) malloc(sizeof(VectArray));
    throwMallocErrorIfTrue(vectArray == NULL);
    vectArray->size = 0;
    vectArray->realSize = 1;
    vectArray->array = (Vect **) malloc(sizeof(Vect *));
    throwMallocErrorIfTrue(vectArray->array == NULL);
    vectArray->array[0] = NULL;
    return vectArray;
}

/**
 * @brief Libère la mémoire d'un tableau de vecteur
 * 
 * @param vectArray 
 */
void freeVectArray(VectArray *vectArray) {
    free(vectArray->array);
    free(vectArray);
}

/**
 * @brief Ajoute un élément dans le tableau de vecteur.
 * 
 * @param vectArray tableau de vecteur ciblé
 * @param vect vecteur à ajouter
 */
void vectArrayAdd(VectArray *vectArray, Vect *vect) {
    vectArray->array = (Vect **) realloc(vectArray->array, sizeof(Vect *) * (vectArray->realSize + 1));
    throwMallocErrorIfTrue(vectArray->array == NULL);
    vectArray->array[vectArray->size] = vect;
    vectArray->array[vectArray->realSize] = NULL;
    vectArray->realSize++;
    vectArray->size++;
}

/**
 * @brief Place un vecteur à un indice du tableau de vecteur.
 * 
 * @param vectArray tableau de vecteur ciblé
 * @param vect vecteur à ajouter
 * @param index indice du tableau de vecteur ou il faut placer le vecteur
 */
void vectArraySet(VectArray *vectArray, Vect *vect, int index) {
    vectArray->array[index] = vect;
}

/**
 * @brief Etant la taille du tableau de vecteur.
 * 
 * @param vectArray tableau de vecteur ciblé
 * @param size nombre de case supplémentaire à ajouter dans le tableau de vecteur
 */
void expendVectArraySize(VectArray *vectArray, int size) {
    vectArray->array = (Vect **) realloc(vectArray->array, sizeof(Vect *) * (vectArray->realSize + size));
    throwMallocErrorIfTrue(vectArray->array == NULL);

    for (int i = vectArray->realSize; i < vectArray->realSize + size; i++) {
        vectArray->array[i] = NULL;
    }

    vectArray->realSize += size;
}

/**
 * @brief Récupère le vecteur à un indice dans un tableau de vecteur.
 * 
 * @param vectArray tableau de vecteur ciblé
 * @param index indice du tableau ou il faut piocher
 * @return Vect* vecteur associé
 */
Vect *vectArrayGet(VectArray *vectArray, int index) {
    return vectArray->array[index];
}

/**
 * @brief Détermine l'indice d'un vecteur dans un tableau de vecteur s'il existe.
 * Sinon, renvoie -1;
 * 
 * @param vectArray tableau de vecteur
 * @param vect vecteur à rechercher
 * @return int indice du vecteur dans le tableau de vecteur
 */
int getIndexOfVectInVectArray(VectArray *vectArray, Vect *vect) {
    for (int i = 0; i < vectArray->size; i++) {
        if (vectEqualsToVect(vectArray->array[i], vect)) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Détermine si un vecteur se trouve dans un tableau de vecteur
 * 
 * @param vectArray tableau de vecteur ciblé
 * @param vect vecteur recherché
 * @return true si le vecteur se trouve dans le tableau de vecteur
 * @return false si le tableau ne se trouve pas dans le tableau de vecteur
 */
bool vectIsInVectArray(VectArray *vectArray, Vect *vect) {
    return getIndexOfVectInVectArray(vectArray, vect) != -1;
}