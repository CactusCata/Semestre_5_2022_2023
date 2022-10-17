#include "main.h"

int main(int argc, char *argv[]) {

  GraphM g = initGraphMFromFile("../data/graph1.graphM");
  printGraphM(g);

  writeGraphMInFile(g, "../data/loool.graphM");

  drawGraphM(g, "../data/", "test2");

  printf("Le nombre de composante de G est: %ld\n", getComposanteConnexeAmountM(g));

  freeGraphM(g);


  GraphL g2 = initGraphLFromFile("../data/graphTest.graphL");
  printGraphL(g2);

  drawGraphL(g2, "../data/", "test4");

  freeGraphL(g2);

  return 0;
}
