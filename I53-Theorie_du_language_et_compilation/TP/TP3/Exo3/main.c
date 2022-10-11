#include "main.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Veuillez préciser le nom du fichier contenant les règles re.\n");
        return 0;
    }

    if (argc < 3) {
        printf("Veuillez préciser le nom du fichier à analyser.\n");
        return 0;
    }

    char *regFileName = argv[1];
    char *textFileName = argv[2];

    printf("Création de la table unilex...\n");
    unsigned int arraySize = 0;
    unilex_t *unilexArray = creer_unilex_table(regFileName, &arraySize);
    printf("Table unilex créée\n");

    printf("Génération des unitées lexicales...\n");
    Queue *lexicalsUnits = getLexicalsUnits(textFileName, unilexArray, arraySize);
    printf("Génération terminée\n");
    printQueue(lexicalsUnits);
    

    freeQueue(lexicalsUnits);


    return 0;

}