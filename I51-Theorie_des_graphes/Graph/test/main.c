#include "main.h"

int main(int argc, char *argv[]) {

  GraphM g = initGraphMFromFile("../data/graph1.graphM");
  printGraphM(g);

  writeGraphMInFile(g, "../data/loool.graphM");

  drawGraphM(g, "../data/", "test2");

  printf("Le nombre de composante de G est: %lld\n", getComposanteConnexeAmountM(g));

  freeGraphM(g);


  GraphL g2 = initGraphLFromFile("../data/graphTest.graphL");
  printf("Passed\n");
  printGraphL(g2);

  freeGraphL(g2);

  return 0;
}
