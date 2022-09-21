#include "main.hpp"

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        std::cout << "You must specify an arithmetic sentence." << std::endl;
        return 1;
    }


    std::string text = charsToString(argv[1]);
    std::string lexicalAnalyse = erase(text, ' ');
    lexicalAnalyse = analex(lexicalAnalyse);
    std::cout << "Résultat: " << lexicalAnalyse << std::endl;

    //char *arithmeticSentence = argv[1];
    //isCorrect(arithmeticSentence);

}
