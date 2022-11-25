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

  point *points = nuages(5);
  drawPoints("data/", "cloud", points, 5);
  dotToImage("data/", "cloud");
  openImage("data/", "cloud", "png");
  free(points);

  return 0;
}
