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

  char textBuffer[32];
  for (float i = -1; i <= 1; i += 0.1) {
    sprintf(textBuffer, "randGraph%f", i);
    GraphL g = randomGraph(6, i);
    drawGraphL(g, "../data/", textBuffer);
    freeGraphL(g);
  }

  return 0;
}
