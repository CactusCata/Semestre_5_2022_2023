#include "main.h"

int main(int argc, char *argv[]) {

  /**
  GraphM g = initGraphMFromFile("../data/graph1.graphM");
  printGraphM(g);

  writeGraphMInFile(g, "../data/loool.graphM");

  drawGraphM(g, "../data/", "test2");

  printf("Le nombre de composante de G est: %ld\n", getComposanteConnexeAmountM(g));

  freeGraphM(g);
  */

  /**
  GraphL g2 = initGraphLFromFile("../data/graphTest.graphL");
  printGraphL(g2);

  drawGraphL(g2, "../data/", "test4");

  freeGraphL(g2);
  */

  /**
  Pair *pairs = generatePairEnum(6);
  GraphL g = intToGraph(623, 6, pairs);
  printGraphL(g);
  drawGraphL(g, "../data/", "tmp");
  printf("La composante de taille maximale est: %d\n", geante(g));


  int n = 7;
  printf("Proportion connexe pour n = %d vaut %d\n", n, proportionConnexe(n));
  */

  /*
  int n = atoi( argv[1] );
  point *points = nuages(n);
  //drawPoints("data/", "cloud", points, n);
  //dotToImage("data/", "cloud");

  GraphAcm graphAcm = acm(points, n);
  approximation(graphAcm.graph, 0);
  drawGraphAcm(graphAcm, "data/", "acm");

  freeGraphAcm(graphAcm);

  openImage("data/", "cloud", "png");
  free(points);
  */

  /*
  if (argc < 2) {
    printf("Vous devez préciser la valeur maximale de partition a tester.\n");
    printf("usage: %s <n>\n", argv[0]);
    return 1;
  }

  int n = atoi(argv[1]);
  int *t = (int *) calloc(sizeof(int), (n + 1));
  int solution = 0;
  clock_t begin = clock();
  partition(1, n, t, &solution);
  clock_t end = clock() - begin;
  free(t);

  printf("%d %ld\n", n, end);
  */

  GraphM g = initGraphMFromFile("data/clique.graphM");
  getMaximumClique(&g);
  freeGraphM(g);

  return 0;
}
