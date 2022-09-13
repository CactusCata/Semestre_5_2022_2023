#include "main.hpp"

int main(int argc, char *argv[]) {

    if (argc < 1) {
        std::cout << "You must specify an arithmetic sentence." << std::endl;
        return 1;
    }

    char *arithmeticSentence = argv[1];
    isCorrect(arithmeticSentence);

}