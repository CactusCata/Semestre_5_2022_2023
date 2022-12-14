#include "graphListAdj.h"

GraphL initGraphL(unsigned int edgeAmount) {
  GraphL graph;
  graph.edgeAmount = edgeAmount;

  Stack *listAdj = (Stack *) malloc(sizeof(Stack) * edgeAmount);

  for (size_t i = 0; i < edgeAmount; i++) {
    listAdj[i].first = NULL;
    listAdj[i].size = 0;
  }

  graph.listAdj = listAdj;
  return graph;
}

GraphL initGraphLFromFile(char *fileName) {
  FILE *file = fopen(fileName, "r");

  if (!file) {
    printf("Aucun fichier avec le nom '%s'.\n", fileName);
    exit(1);
  }

  GraphL graph;
  unsigned int edgeAmount = 0;
  unsigned char foundEdgeAmount = 0;

  char *lineFileBuffer = (char *) malloc(sizeof(char) * 1024);
  while (fgets(lineFileBuffer, 1024, file)) {
    if (lineFileBuffer[0] == 'e') {
      if (!sscanf(lineFileBuffer, "edgeAmount=%d\n", &edgeAmount)) {
        printf("Vous devez indiquer l'ordre du graph en premier.");
        exit(1);
      }
      foundEdgeAmount = 1;
      graph = initGraphL(edgeAmount);
    } else {
      if (!foundEdgeAmount) {
        printf("Vous devez indiquer l'ordre du graph en premier.");
        exit(1);
      }
      size_t cursor = 0;
      int sommet = readNextUInt(lineFileBuffer, &cursor);
      cursor++; // count the ':'
      Stack *stackSommet = &graph.listAdj[sommet];

      int sommetAdj = -1;
      cursor++; // count the space
      while ((sommetAdj = readNextUInt(lineFileBuffer, &cursor)) != -1) {
        push(stackSommet, sommetAdj);
        cursor++; // count the potential space
        //push(&graph.listAdj[neighboorSommet], sommet); add on neighboor the sommet
      }
    }
  }

  free(lineFileBuffer);
  fclose(file);

  return graph;
}

void writeGraphLInFile(GraphL graph, char *fileName) {
  FILE *file = fopen(fileName, "w");

  fprintf(file, "edgeAmount=%d\n", graph.edgeAmount);

  for (size_t s = 0; s < graph.edgeAmount; s++) {
    Stack *stack = &graph.listAdj[s];

    if (!stackIsEmpty(stack)) {
      char *lineSommet = (char *) malloc(sizeof(char) * 1024);
      size_t lineSommetCursor = 0;

      // Ecrit le sommet concern??
      char *sommetStr = intToStr(s);
      appendText(lineSommet, &lineSommetCursor, sommetStr);
      free(sommetStr);
      appendText(lineSommet, &lineSommetCursor, ":");

      SElement *element = stack->first;
      while (element) {
        char *sommetStr = intToStr(element->value);
        appendText(lineSommet, &lineSommetCursor, " ");
        appendText(lineSommet, &lineSommetCursor, sommetStr);
        free(sommetStr);
        element = element->next;
      }
      fprintf(file, "%s\n", lineSommet);
      free(lineSommet);
    }
  }
  fclose(file);
}

void freeGraphL(GraphL graph) {
  for (size_t s = 0; s < graph.edgeAmount; s++) {
    freeStack(&(graph.listAdj[s]));
  }
  free(graph.listAdj);
}

void printGraphL(GraphL graph) {
  unsigned int n = graph.edgeAmount;
  printf("edgeAmount=%d\n", n);
  printf("[\n");
  for (unsigned int i = 0; i < n - 1; i++) {
    printf("\t");
    printStack(&graph.listAdj[i]);
    printf(",\n");
  }
  printf("\t");
  printStack(&graph.listAdj[n - 1]);
  printf("\n");
  printf("]\n");
}

void drawGraphL(GraphL graph, char *path, char *fileName) {
  unsigned int n = graph.edgeAmount;

  char filePathNameExtension[256];
  sprintf(filePathNameExtension, "%s%s.dot", path, fileName);
  FILE *file = fopen(filePathNameExtension, "w");

  fprintf(file, "graph A {\n");

  for (unsigned int s = 0; s < n; s++) {
    char *lineBuffer = (char *) malloc(sizeof(char) * 2048);
    size_t cursor = 0;

    Stack *stack = &(graph.listAdj[s]);

    appendText(lineBuffer, &cursor, "\t");
    char *sommetStr = intToStr(s);
    appendText(lineBuffer, &cursor, sommetStr);
    free(sommetStr);

    appendText(lineBuffer, &cursor, " -- {");
    SElement *current = stack->first;
    unsigned char isFirstElement = 1;

    while (current) {
      if (current->value < s) {
        current = current->next;
        continue;
      }

      if (!isFirstElement) {
        appendText(lineBuffer, &cursor, " ");

      }

      if (isFirstElement) {
        isFirstElement = 0;
      }

      char *sommetAdjStr = intToStr(current->value);
      appendText(lineBuffer, &cursor, sommetAdjStr);
      free(sommetAdjStr);

      current = current->next;
    }
    appendText(lineBuffer, &cursor, "};\n");
    fputs(lineBuffer, file);
    free(lineBuffer);
  }

  fprintf(file, "}");
  fclose(file);

  char cmd[512];
  sprintf(cmd, "dot -Tpng %s > %s%s.png", filePathNameExtension, path, fileName);
  system(cmd);
}

size_t getComposanteConnexeAmountRecL(GraphL graph) {
  unsigned char *reached = (unsigned char *) calloc(sizeof(unsigned char), graph.edgeAmount);
  size_t composanteConnexeAmount = 0;
  for (size_t s = 0; s < graph.edgeAmount; s++) {
    if (!reached[s]) {
      composanteConnexeAmount++;
      reachAllNeighborsRecL(s, graph, reached);
    }
  }
  free(reached);
  return composanteConnexeAmount;
}

void reachAllNeighborsRecL(size_t s, GraphL graph, unsigned char *reached) {
  reached[s] = 1;
  SElement *element = graph.listAdj[s].first;
  while (element) {
    if (reached[element->value] == 0) {
      reachAllNeighborsRecL(element->value, graph, reached);
    }
    element = element->next;
  }
}

size_t getComposanteConnexeAmountIteL(GraphL graph) {
  unsigned char *reached = (unsigned char *) calloc(sizeof(unsigned char), graph.edgeAmount);
  size_t composanteConnexeAmount = 0;
  for (size_t s = 0; s < graph.edgeAmount; s++) {
    if (!reached[s]) {
      composanteConnexeAmount++;
      reachAllNeighborsIteL(s, graph, reached);
    }
  }
  free(reached);
  return composanteConnexeAmount;
}

void reachAllNeighborsIteL(size_t s, GraphL graph, unsigned char *reached) {
  Stack *stack = createStack();
  Stack *aux;
  push(stack, s);
  reached[s] = 1;

  while (!stackIsEmpty(stack)) {
    int sommet = pop(stack);
    aux = &graph.listAdj[sommet];
    SElement *currentElement = aux->first;
    while (currentElement) {
      if (reached[currentElement->value] == 0) {
        push(stack, currentElement->value);
        reached[currentElement->value] = 1;
      }
      currentElement = currentElement->next;
    }
  }
  free(stack);
}

unsigned char isConnexe(GraphL graph) {
  unsigned char *reached = (unsigned char *) calloc(sizeof(unsigned char), graph.edgeAmount - 1);
  reachAllNeighborsIteL(0, graph, reached);

  for (unsigned int i = 0; i < graph.edgeAmount - 1; i++) {
    if (!reached[i]) {
      free(reached);
      return 0;
    }
  }

  free(reached);
  return 1;
}


unsigned int proportionConnexe(int order) {
  int max = 1 << ((order * (order - 1)) / 2);
  Pair *pairs = generatePairEnum(order);
  unsigned int cpt = 0;

  for (unsigned int k = 0; k < max; k++) {
    GraphL g = intToGraph(k, order, pairs);
    if (isConnexe(g)) {
      cpt++;
    }
    freeGraphL(g);
  }
  free(pairs);
  return cpt;
}

GraphL intToGraph(unsigned int n, int order, Pair *pairs) {
  GraphL g = initGraphL(order);
  int k = 0;

  while (n) {
    if (n & 1) {
      Stack *stack = &g.listAdj[pairs[k].e1];
      push(stack, pairs[k].e2);
    }
    k++;
    n >>= 1;
  }
  return g;
}

void reachAllNeighborsRecLAndRecord(unsigned int s, GraphL graph, unsigned char *reached, unsigned int *sizeComposante) {
  reached[s] = 1;
  SElement *element = graph.listAdj[s].first;
  while (element) {
    if (reached[element->value] == 0) {
      (*sizeComposante)++;
      reachAllNeighborsRecLAndRecord(element->value, graph, reached, sizeComposante);
    }
    element = element->next;
  }
}

unsigned int geante(GraphL graph) {
  unsigned int maxC = 1;
  unsigned char *reached = (unsigned char *) calloc(sizeof(unsigned char), graph.edgeAmount);

  for (unsigned int s = 0; s < graph.edgeAmount - maxC; s++) {
    if (reached[s] == 0) {
      unsigned int sizeComposante = 1; // peut etre 0
      reachAllNeighborsRecLAndRecord(s, graph, reached, &sizeComposante);
      if (sizeComposante > maxC) {
        maxC = sizeComposante;
      }
    }
  }

  free(reached);
  return maxC;
}

unsigned int getDegree(GraphL graph, unsigned int sommet) {
  return graph.listAdj[sommet].size;
}

InfoGraph *getInfosGraph(GraphL graph) {
  InfoGraph *infos = (InfoGraph *) malloc(sizeof(InfoGraph) * graph.edgeAmount);
  unsigned char *reached = (unsigned char *) calloc(sizeof(unsigned char), graph.edgeAmount);


  free(reached);
  return infos;
}