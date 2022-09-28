#include "main.hpp"

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        std::cout << "You must specify a file or an arithmetic sentence." << std::endl;
        return 1;
    }

    std::ifstream arithmeticFile(argv[1]);
    std::string text;

    if (!arithmeticFile) {
        std::cout << "File not found, try to resolve as arithmetic expression." << std::endl;
        text = charsToString(argv[1]);
    } else {
        std::getline(arithmeticFile, text);
    }

    std::string lexicalAnalyse = erase(text, ' ');
    std::vector<LexiconPart *> lexiconsParts = analex(lexicalAnalyse);

    for (unsigned int i = 0; i < lexiconsParts.size() - 1; i++) {
        std::cout << lexiconsParts.at(i)->serialize() << ','; 
    }
    std::cout << lexiconsParts.at(lexiconsParts.size() - 1)->serialize() << std::endl;

    Queue queue = analSynthax(lexiconsParts);
    
    createThreeAddressCode("a.out", queue);



}
