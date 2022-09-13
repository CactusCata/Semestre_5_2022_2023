#include "graph.hpp"

char *reached;

Graph init(const unsigned int &n) {
    Graph g;
    g.ordre = n;
    char **matriceAdjacence = new char*[n];
    for (unsigned int i = 0; i < n; i++) {
        char *line = new char[n];
        for (unsigned int j = 0; j < n; j++) {
            line[j] = 0;
        }
        matriceAdjacence[i] = line;
    }
    g.matriceAdjacence = matriceAdjacence;
    return g;
}

Graph readGraph(const std::string &fileName) {
    std::ifstream file;
    file.open(fileName, std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Error: Le fichier " << fileName << " n'a pas été trouvé." << std::endl;
        exit(1);
    }

    Graph g;
    std::string line;
    while (getline(file, line)) {
        if (line.substr(0, 4) == "nbs=") {
            unsigned int ordre;
            sscanf(line.c_str(), "nbs=%d", &ordre);
            g = init(ordre);
        } else if (line[0] >= '0' && line[0] <= '9') {
            if (g.matriceAdjacence == nullptr) {
                std::cerr << "Veuillez préciser le nombre de sommet." << std::endl;
                exit(1);
            }
            int l, r;
            sscanf(line.c_str(), "%d %d", &l, &r);
            g.matriceAdjacence[l][r] = 1;
            g.matriceAdjacence[r][l] = 1;
        }
    }

    file.close();
    return g;
}

void printGraph(const Graph &g) {
    std::cout << "Ordre de g: " << g.ordre << std::endl;
    for (unsigned int i = 0; i < g.ordre; i++) {
        for (unsigned int j = 0; j < g.ordre; j++) {
            char res = g.matriceAdjacence[i][j] ? '1' : '0';
            std::cout << res << " ";
        }
        std::cout << std::endl;
    }
}

unsigned int getConnexeComposantesAmount(const Graph &g) {
    reached = new char[g.ordre];
    for (unsigned int i = 0; i < g.ordre; i++) {
        reached[i] = '0';
    }

    unsigned int connexeComposantesAmount = 0;
    for (unsigned int s = 0; s < g.ordre; s++) {
        if (reached[s] == '0') {
            connexeComposantesAmount++;
            reachNeighbor(s, g);
        }
    }
    delete reached;
    return connexeComposantesAmount;
}

void reachNeighbor(const unsigned int &s, const Graph &g) {
    if (reached[s] == '0') {
        reached[s] = '1';
        for (unsigned int i = 0; i < g.ordre; i++) {
            if (g.matriceAdjacence[s][i]) {
                reachNeighbor(i, g);
            }
        }
    }
}

bool isConnexe(const Graph &g) {
    reached = new char[g.ordre];
    for (unsigned int i = 0; i < g.ordre; i++) {
        reached[i] = '0';
    }

    reachNeighbor(0, g);

    for (unsigned int i = 0; i < g.ordre; i++) {
        if (reached[i] == '0') {
            delete reached;
            return false;
        }
    }

    delete reached;
    return true;
}

bool isEulerien(const Graph &g) {
    reached = new char[g.ordre];
    for (unsigned int i = 0; i < g.ordre; i++) {
        reached[i] = '0';
    }

    if (!isConnexe(g)) {
        delete reached;
        return false;
    }

    for (unsigned int s = 0; s < g.ordre; s++) {
        unsigned int edgeAmount = 0;
        for (unsigned int col = 0; col < g.ordre; col++) {
            if (g.matriceAdjacence[s][col] == 1) {
                edgeAmount++;
            }
        }
        
        if (edgeAmount & 1) {
            delete reached;
            return false;
        }
    }

    delete reached;
    return true;
}