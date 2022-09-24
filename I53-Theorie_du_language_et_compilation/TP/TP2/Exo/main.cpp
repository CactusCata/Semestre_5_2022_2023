#include "main.hpp"

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        std::cout << "You must specify an arithmetic sentence." << std::endl;
        return 1;
    }


    std::string text = charsToString(argv[1]);
    std::string lexicalAnalyse = erase(text, ' ');
    std::vector<LexiconPart *> lexiconsParts = analex(lexicalAnalyse);

    for (unsigned int i = 0; i < lexiconsParts.size() - 1; i++) {
        std::cout << lexiconsParts.at(i)->serialize() << ','; 
    }
    std::cout << lexiconsParts.at(lexiconsParts.size() - 1)->serialize() << std::endl;

    isCorrect(lexiconsParts);

}
