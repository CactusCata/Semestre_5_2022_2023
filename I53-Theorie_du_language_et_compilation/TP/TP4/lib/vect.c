#include "vect.h"

/**
 * @brief Crée un vecteur
 * 
 * @param needShorted le vecteur a t'il besoin d'être trié ?
 * @return Vect* 
 */
Vect *createVect(bool needShorted) {
    Vect *vect = (Vect *) malloc(sizeof(Vect));
    throwMallocErrorIfTrue(vect == NULL);
    int *array = (int *) malloc(sizeof(int));
    throwMallocErrorIfTrue(array == NULL);
    array[0] = -1;
    vect->array = array;
    vect->realSize = 1;
    vect->size = 0;
    vect->needSorted = needShorted;
    return vect;
}

/**
 * @brief Crée un vecteur à partir d'un tableau
 * 
 * @param array tableau sur lequel se baser
 * @param arraySize taille du tableau
 * @param needShorted le vecteur a t'il besoin d'être trié ?
 * @return Vect* 
 */
Vect *createVectFromIntArray(int *array, int arraySize, bool needShorted) {
    int *arrayCopy = copyArray(array, arraySize);
    if (needShorted) {
        sortArray(arrayCopy, arraySize);
    }
    int *sortedArray = realloc(arrayCopy, sizeof(int) * (arraySize + 1));
    throwMallocErrorIfTrue(sortedArray == NULL);
    sortedArray[arraySize] = -1;
    Vect *vect = (Vect *) malloc(sizeof(Vect));
    throwMallocErrorIfTrue(vect == NULL);
    vect->array = sortedArray;
    vect->size = arraySize;
    vect->realSize = arraySize + 1;
    vect->needSorted = needShorted;
    return vect;
}

/**
 * @brief Libère la mémoire pour un vecteur
 * 
 * @param vect le vecteur ciblé
 */
void freeVect(Vect *vect) {
    free(vect->array);
    free(vect);
}

/**
 * @brief Détermine si un vecteur est vide
 * 
 * @param vect le vecteur ciblé
 * @return true si le vecteur est vide
 * @return false si le vecteur n'est pas vide
 */
bool vectIsEmpty(Vect *vect) {
    return vect->size == 0;
}

/**
 * @brief Détermine l'indice idéal pour le placement d'une valeur dans un vecteur.
 * A utiliser uniquement sur un vecteur trié.
 * A améliorer puisque la liste est triée Theta(vect.size) --> Theta(log2(vect.size)).
 * 
 * @param vect le vecteur ciblé
 * @param value la valeur à placer
 * @return int l'indice idéal
 */
int getBestVectIndex(Vect *vect, int value) {
    int index = 0;
    while (vect->array[index] < value && vect->array[index] != -1) {
        index++;
    }
    return index;
}

/**
 * @brief Ajoute un élément dans le vecteur. Gère à la fois le cas d'un vecteur trié d'un
 * vecteur non trié.
 * 
 * @param vect le vecteur ciblé 
 * @param value valeur à ajouter dans le vecteur
 */
void vectAdd(Vect *vect, int value) {
    if (vect->needSorted) {
        expendVectSize(vect, 1);
        int index = getBestVectIndex(vect, value);
        shiftValuesArrayToRight(vect->array, vect->realSize, index);
        vect->array[index] = value;
    } else {
        if (vect->realSize - 1 == vect->size) {
            expendVectSize(vect, 1);
        }
        vect->array[vect->size] = value;
    }

    vect->size++;
}

/**
 * @brief Place une valeur dans un vecteur. A ne pas utiliser sur un vecteur trié, cela risque
 * de compromettre son ordonnancement.
 * 
 * @param vect le vecteur ciblé
 * @param value valeur à ajouter dans le vecteur
 * @param index indice auquel il faut placer la valeur dans le vecteur
 */
void vectSet(Vect *vect, int value, int index) {
    vect->array[index] = value;
    if (vect->needSorted) {
        printf("Waring, action \"vectSet(vect: vect, value: %d, index: %d)\" is not appropriate on sorted vect !\n", value, index);
        printf("The array may loose sorted proporty.\n");
    }
}

/**
 * @brief Détermine si une valeur est contenue dans le vecteur.
 * 
 * @param vect vecteur ciblé
 * @param value valeur à rechercher dans le vecteur
 * @return true si la valeur est dans le vecteur.
 * @return false si la valeur n'est pas dans le vecteur
 */
bool vectContrainsValue(Vect *vect, int value) {
    for (int i = 0; i < vect->size; i++) {
        if (vect->array[i] == value) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Etant la taille du vecteur
 * 
 * @param vect le vecteur ciblé
 * @param size nombre de case supplémentaire à allouer
 */
void expendVectSize(Vect *vect, int size) {
    vect->array = realloc(vect->array, sizeof(Vect) * (vect->realSize + size));
    throwMallocErrorIfTrue(vect->array == NULL);

    for (int i = vect->realSize; i < vect->realSize + size; i++) {
        vect->array[i] = -1;
    }

    vect->realSize += size;
}

/**
 * @brief Calcul l'occurence des valeurs identiques entre deux vecteurs.
 * 
 * @param v1 vecteur
 * @param v2 vecteur
 * @return int occurence des valeurs identiques entre les deux vecteurs
 */
int sameValuesOccurenciesInVect(Vect *v1, Vect *v2) {
    int indexV1 = 0;
    int indexV2 = 0;
    int count = 0;

    while (indexV1 != v1->size && indexV2 != v2->size) {
        if (v2->array[indexV2] < v1->array[indexV1]) {
            indexV2++;
        } else if (v2->array[indexV2] == v1->array[indexV1]) {
            count++;
            indexV1++;
            indexV2++;
        } else {
            indexV1++;
        }
    }
    return count;
}

/**
 * @brief Détermine la réunion de deux vecteurs.
 * 
 * @param v1 vecteur
 * @param v2 vecteur
 */
void unionVectAsSet(Vect *v1, Vect *v2) {

    if (!vectIsEmpty(v2)) {
        expendVectSize(v1, v2->size - sameValuesOccurenciesInVect(v1, v2));

        int indexV1 = 0;
        int indexV2 = 0;
        while (indexV2 < v2->size) {
            if (v1->array[indexV1] == -1) { // Fin de vect->array
                v1->array[indexV1] = v2->array[indexV2];
                indexV1++;
                v1->size++;
                indexV2++;
            } else if (v2->array[indexV2] < v1->array[indexV1]) {
                shiftValuesArrayToRight(v1->array, v1->realSize, indexV1);
                v1->array[indexV1] = v2->array[indexV2];
                indexV1++;
                v1->size++;
                indexV2++;
            } else if (v2->array[indexV2] == v1->array[indexV1]) {
                indexV1++;
                indexV2++;
            } else {
                indexV1++;
            }
        }
    }

}

/**
 * @brief Détermine si l'intersection de deux vecteurs de n'est pas vide
 * 
 * @param v1 vecteur
 * @param v2 vecteur
 * @return true s'il existe un élément dans v1 qui soit dans v2
 * @return false s'il n'existe pas d'élément dans v1 qui soit dans v2
 */
bool intersectionOfVectIsNotEmpty(Vect *v1, Vect *v2) {

    if (v1->size != v2->size) {
        return true;
    }

    int index = 0;
    while (index != v1->size) {
        if (v1->array[index] != v2->array[index]) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Renvoie sous la forme de chaine de caractère le vecteur
 * 
 * @param vect vecteur ciblé
 * @return char* vecteur sous la forme d'une chaine de caractère
 */
char *serializeVect(Vect *vect) {
    char *text = serializeSet(vect->array, vect->size);
    int textCursorW = strlen(text);
    char textBuffer[128];
    sprintf(textBuffer, "\nSize = %d\nRealSize = %d\n", vect->size, vect->realSize);
    appendText(text, textBuffer, &textCursorW);
    return text;
}

/**
 * @brief Renvoie sous la forme d'une chaine de caractère le vecteur en affichant aussi
 * ses valeurs de contrôle (-1).
 * 
 * @param vect vecteur ciblé
 * @return char* chaine de caractère du vecteur avec ses valeurs de contrôle (-1)
 */
char *serializeRealVect(Vect *vect) {
    char *text = serializeSet(vect->array, vect->realSize);
    int textCursorW = strlen(text);
    char textBuffer[128];
    sprintf(textBuffer, "\nSize = %d\nRealSize = %d", vect->size, vect->realSize);
    appendText(text, textBuffer, &textCursorW);
    return text;
}

/**
 * @brief Ecrit sur la sortie standard les données d'un vecteur
 * 
 * @param vect vecteur ciblé
 */
void printVect(Vect *vect) {
    char *text = serializeRealVect(vect);
    puts("--------------------------------------");
    printf("%s", text);
    puts("\n");
    free(text);
}

/**
 * @brief Renvoie la chaine de cractère correspondant à un vecteur.
 * 
 * @param vect vecteur ciblé
 * @return char* chaine de caractère correspondant au vecteur
 */
char *serializeVectArray(Vect *vect) {
    return serializeSet(vect->array, vect->size);
}

/**
 * @brief Ecrit sur la sortie standard le tableau correspondant au tableau contenu dans le vecteur
 * 
 * @param vect 
 */
void printVectArray(Vect *vect) {
    char *text = serializeSet(vect->array, vect->size);
    puts(text);
    free(text);
}

/**
 * @brief Renvoie le tableau d'entier associé à un vecteur
 * 
 * @param vect vecteur ciblé
 * @return int* tableau du vecteur en paramètre
 */
int *vectToIntArray(Vect *vect) {
    return vect->array;
}

/**
 * @brief Converti un tableau en vecteur.
 * 
 * Est-ce bien utile ? fonction createVect(array) déjà existante 
 * 
 * @param array tableau à convertir
 * @param stopValue valeur de contrôle pour déterminer la fin du tableau lu
 * @return Vect* vecteur déterminé
 */
Vect *intArrayToVect(int *array, int stopValue) {
    Vect *vect = (Vect *) malloc(sizeof(Vect));
    throwMallocErrorIfTrue(vect == NULL);

    int arrayRealSize = 1;
    while (array[arrayRealSize] != stopValue) {
        arrayRealSize++;
    }

    vect->array = array;
    vect->realSize = arrayRealSize;
    vect->size = arrayRealSize - 1;

    return vect;
}

/**
 * @brief Récupère l'entier à l'indice spécifié dans un vecteur
 * 
 * @param vect vecteur ciblé
 * @param index indice choisi
 * @return int valeur à l'indice
 */
int vectGet(Vect *vect, int index) {
    return vect->array[index];
}

/**
 * @brief Détermine si deux vecteurs sont égaux
 * 
 * @param v1 vecteur 1
 * @param v2 vecteur 2
 * @return true si les vecteurs sont égaux
 * @return false si les vecteurs ne sont pas égaux
 */
bool vectEqualsToVect(Vect *v1, Vect *v2) {
    if (v1->size != v2->size) {
        return false;
    }

    for (int i = 0; i < v1->size; i++) {
        if (v1->array[i] != v2->array[i]) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Crée une copie d'un vecteur
 * 
 * @param vect vecteur ciblé
 * @return Vect* copie du vecteur
 */
Vect *vectCopy(Vect *vect) {
    Vect *vectCopy = createVect(vect->needSorted);
    expendVectSize(vectCopy, vect->size);

    for (int i = 0; i < vect->size; i++) {
        vectCopy->array[i] = vect->array[i];
    }

    vectCopy->size = vect->size;

    return vectCopy;
}