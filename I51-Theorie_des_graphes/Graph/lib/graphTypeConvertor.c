#include "graphTypeConvertor.h"

GraphL graphMat2Adj(GraphM graphM) {
    GraphL graphL;
    graphL.edgeAmount = graphM.edgeAmount;
    graphL.listAdj = (Stack *) calloc(graphM.edgeAmount, sizeof(Stack *));

    for (size_t s = 0; s < graphM.edgeAmount; s++) {
        for (size_t t = 0; t < graphM.edgeAmount; t++) {
            if (graphM.matrixAdj[s][t]) {
                push(&graphL.listAdj[s], t);
            }
        }
    }

    return graphL;
}