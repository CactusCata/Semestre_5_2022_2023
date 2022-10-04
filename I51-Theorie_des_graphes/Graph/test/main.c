#include "main.h"

int main(int argc, char *argv[]) {

  Graph g = readGraph("../data/graph1.dat");
  printGraph(g);

  writeGraph(g, "../data/loool.dat");

  drawGraph(g, "../data/", "test2");

  return 0;
}
