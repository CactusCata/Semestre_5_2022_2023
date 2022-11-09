#include "graphviz.h"

/**
 * @brief Initialisation d'un fichier .dot pour GraphViz
 * 
 * @param file fichier cible
 */
void graphVizInitGraph(FILE *file) {
    fputs("digraph G {\n", file);
}

/**
 * @brief Ajoute un état initial au fichier .dot pour GraphViz.
 * Nécéssite au préalable l'appel de la fontion graphVizInitGraph().
 * 
 * @param file fichier cible
 * @param q état initial concerné
 */
void graphVizAddInitialState(FILE *file, int q) {
    fprintf(file, "\tn%d [label= \"\", shape=none,height=.0,width=.0];\n", q);
    fprintf(file, "\tn%d -> %d;\n", q, q);
}

/**
 * @brief Ajoute un état final au fichier .dot pour GraphViz.
 * Nécéssite au préalable l'appel de la fonction graphVizInitGraph().
 * 
 * @param file fichier cible
 * @param q état final concerné
 */
void graphVizAddFinalState(FILE *file, int q) {
    fprintf(file, "\t%d [peripheries=2];\n", q);
}

/**
 * @brief Ajoute une transition au fichier .dot pour GraphViz.
 * Nécéssite au préalable l'appel de la fonction graphVizInitGraph().
 * 
 * @param file fichier cible
 * @param q1 état antécédant
 * @param symbol symbol permettant la transisition
 * @param q2 état image
 */
void graphVizAddTransition(FILE *file, int q1, char symbol, int q2) {
    if (symbol == '&') {
        fprintf(file, "\t%d -> %d [label=\" &#949;\"];\n", q1, q2);
    } else {
        fprintf(file, "\t%d -> %d [label=\" %c\"];\n", q1, q2, symbol);
    }
}

/**
 * @brief Permet de finaliser la construction d'un fichier .dot pour GraphViz.
 * 
 * @param file fichier cible
 */
void graphVizEnd(FILE *file) {
    fputs("}\n", file);
}