#include "graphListAdj.h"

GraphL initGraphL(unsigned int edgeAmount) {
  GraphL graph;
  graph.edgeAmount = edgeAmount;

  Stack *listAdj = (Stack *) malloc(sizeof(Stack *) * edgeAmount);
  
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
      printf("EdgeAmount = %d\n", edgeAmount);
      foundEdgeAmount = 1;
      graph = initGraphL(edgeAmount);
      printf("Graph has been init\n");
    } else {
      if (!foundEdgeAmount) {
        printf("Vous devez indiquer l'ordre du graph en premier.");
        exit(1);
      }
      printf("test: %s\n", lineFileBuffer);
      int sommet;
      char *cached = (char *) malloc(sizeof(char) * 1024);
      printf("RES: %d\n", sscanf(lineFileBuffer, "%d: %[^\n]\n", &sommet, cached));
      if (sscanf(lineFileBuffer, "%d: %[^\n]\n", &sommet, cached)) {
        printf("Sommet concerné: %d\n", sommet);
        Stack *stackSommet = &graph.listAdj[sommet];

        int neighboorSommet = -1;
        while (sscanf(lineFileBuffer, " %d", &neighboorSommet)) {
          char numberBuffer[32];
          sprintf(numberBuffer, "%d", neighboorSommet);
          lineFileBuffer += 1 + strlen(numberBuffer);
          push(stackSommet, neighboorSommet);
          //push(&graph.listAdj[neighboorSommet], sommet); add on neighboor the sommet 
        }
      } else {
        printf("OTHER\n");
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
      sprintf(lineSommet, "%lld:", s);

      SElement *element = stack->first;
      while (element) {
        sprintf(lineSommet, "%s %d", lineSommet, element->value);
        element = element->next;
      }
    } 
  }
}

void freeGraphL(GraphL graph) {
  for (size_t s = 0; s < graph.edgeAmount; s++) {
    freeStack(&graph.listAdj[s]);
  }
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

size_t getComposanteConnexeAmountL(GraphL graph) {
  unsigned char *reached = (unsigned char *) calloc(sizeof(unsigned char), graph.edgeAmount);
  size_t composanteConnexeAmount = 0;
  for (size_t s = 0; s < graph.edgeAmount; s++) {
    if (!reached[s]) {
      composanteConnexeAmount++;
      reachAllNeighborsL(s, graph, reached);
    }
  }
  free(reached);
  return composanteConnexeAmount;
}

void reachAllNeighborsL(size_t s, GraphL graph, unsigned char *reached) {
  reached[s] = 1;
  SElement *element = graph.listAdj[s].first;
  while (element) {
    if (reached[element->value] == 0) {
      reachAllNeighborsL(element->value, graph, reached);
    }
    element = element->next;
  }
}