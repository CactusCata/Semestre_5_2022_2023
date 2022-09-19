#include "graph.h"

Graph initGraph(unsigned int order) {
    Graph g;
    g.order = order;

    boolean **matrixAdjacence = (boolean **) calloc(order, sizeof(boolean *));

    for (unsigned int i = 0; i < order; i++) {
        matrixAdjacence[i] = (boolean *) calloc(order, sizeof(boolean));
    }

    g.matrixAdj = matrixAdjacence;
    return g;
}

void deleteGraph(Graph g) {
    for (unsigned int i = 0; i < g.order; i++) {
        free(g.matrixAdj[i]);
    }
    free(g.matrixAdj);
}

Graph readGraph(char *fileName) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        fclose(file);
        perror("File not exist");
        exit(1);
    }

    char buffer[1024];
    char *line = fgets(buffer, 1024, file);
    boolean orderIsInit = false;
    unsigned int order = -1;
    Graph g;

    while (line != NULL) {
        if (line[0] == 'o') {
            printf("In order section");
            if (sscanf(line, "order: %d", &order)) {
                g = initGraph(order);
                orderIsInit = true;
            } else {
                perror("Syntax error");
            }
        } else if (line[0] >= '0' && line[0] <= '9') {
            printf("In graph edge section");
            if (!orderIsInit) {
                perror("You need to write the graph order before edge");
            }
            int leftValue = -1;
            int rightValue = -1;

            if (!sscanf(line, "%d %d", &leftValue, &rightValue)) {
                perror("Syntax error");
            }

            printf("Added");
            g.matrixAdj[leftValue][rightValue] = true;
            g.matrixAdj[rightValue][leftValue] = true;
        }

        line = fgets(buffer, 1024, file);
    }

    fclose(file);
    return g;
}

void writeGraph(Graph g) {

}

void writeGraph2(Graph g) {

}

void printGraph(Graph g) {
    printf("Graph order: %d\n", g.order);
    for (unsigned int i = 0; i < g.order; i++) {
        for (unsigned int j = 0; j < g.order; j++) {
            printf("%d ", g.matrixAdj[i][j]);
        }
        printf("\n");
    }
}

void drawGraph(Graph g) {

}