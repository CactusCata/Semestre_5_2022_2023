#include "graph.hpp"
#include <iostream> 

int main(int argc, char *argv[]) {
    Graph g = init(3);

    printGraph(g);

    std::string fileName("graph1.txt");
    g = readGraph(fileName);
    printGraph(g);
    std::cout << "Le nombre de composantes connexes de g est: " << getConnexeComposantesAmount(g) << std::endl;

    std::cout << "Le graph est connexe: " << isConnexe(g) << std::endl;
    std::cout << "Le graph est eulerien: " << isEulerien(g) << std::endl;
    return 0;
}