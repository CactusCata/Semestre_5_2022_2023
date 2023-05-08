#include "isomorph.h"

GraphM *genGraph(GraphM g) {
    
}

GraphM applyPermOnGraph(GraphM g, int *s) {
    GraphM gPerm = initGraphM(g.edgeAmount);

    // On recopie le contenu de g dans gPerm
    for (int i = 0; i < g.edgeAmount; i++) {
        for (int j = 0; j < g.edgeAmount; j++) {
            gPerm.matrixAdj[s[i]][j] = g.matrixAdj[i][j]
        }
    }
    return gPerm;
}