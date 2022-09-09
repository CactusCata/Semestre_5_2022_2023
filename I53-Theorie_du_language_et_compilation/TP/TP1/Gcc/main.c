#define CARRE(X) ((X)*(X))
#define CUBE(X) (CARRE(X)*(X))
#define DIX 10

/*
    Commentaire sur
    plusieurs
    lignes
*/

int main (int argc , char * argv []) {
    int a = 2, b = 1, c , i;

    // Commentaire sur une seule ligne
    for (i=0; i<DIX ; i++) a++;

    a = a+1;
    b = a+b;
    c = CARRE(a+b) + CUBE(a-b);

    return c;
}

/**
 * Question 1.a: Tester l'effet de l'option -E de gcc. 
 * 
 * On peut observer dans un premier temps que la commande gcc
 * s'est arrêtée dans son execution, après la phase de pré-processeur.
 * 
 * On peut remarquer:
 *  - Un code toujours lisible
 *  - La disparition des commentaires
 *  - Les instructions contenant les macros définies
 *      par le mot clef #define ont été remplacées
 *      par le contenu des macros
 *  - Les macros définies par l'instruction #define
 *      ont été supprimées
 *  - L'ajout d'instructions (?):
 *    # 1 ".\\Gcc\\main.c"
 *    # 1 "<built-in>"
 *    # 1 "<command-line>"
 *    # 1 ".\\Gcc\\main.c"
 *    # 11 ".\\Gcc\\main.c"
 * 
 * 
 *  Question 1.b: Ca rajoute beaucoup de texte.
 *  En réalité, tous le contenu du fichier
 *  d'entête stdio.h on été copié dans le fichier
 *  source.
 */

/**
 * Question 2: Cette option permet de réaliser
 * l'opération de pré-processeur et de compilation.
 * Le fichier de sortie est de la forme
 * d'assembleur

 * L'option -O permet de réduire le
 * nombre d'instruction en assembleur.
 * 
 * (Optimisation)
 *
 */

/**
 * Question 3: Cette operation permet de réaliser
 * de pré-processeur, de compilation et l'assemblage
 * des fichiers sources mais ne réalise pas la phase
 * d'éditeur de lien.
 */