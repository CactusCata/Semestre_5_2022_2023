#include "main.h"

int main(int argc, char *argv[]) {


    Matrix G_generatrice = get_matrix_generatrice();
    matrix_print(G_generatrice, 7, 4, LINE_MAJOR);
    matrix_print(G_generatrice, 7, 4, COL_MAJOR);

    printf("Ensemble de tous les encodages:\n");
    for (Vec v = 0; v < 1 << 4; v++) {
      printf("Vecteur à encoder:\n");
      vec_print(v, 4);
      Vec c = encode(G_generatrice, v, 7, 4);
      printf("\nVecteur encodé:\n");
      vec_print(c, 7);
      printf("\n");
    }

    // Exercice 4.2 a continuer

    matrix_free(G_generatrice);

    return 0;
}
