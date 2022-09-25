#include "threeAddressCode.hpp"

void createThreeAddressCode(std::string fileName, Queue &instructionsQueue) {
    std::ofstream file(fileName);

    unsigned int variableNumber = 1;

    while (!instructionsQueue.isEmpty()) {

        LexiconPart *lp = static_cast<LexiconPart *>(instructionsQueue.get()); 

        if (lp->getLexiconTypeName() == LEXICON_DIGIT_TYPE) {
            file << "t_" << variableNumber << " = " << lp->getString();
        } else {
            file << "t_" << variableNumber - 2 << " = t_" << variableNumber - 2 << " " << lp->getChar() << " t_" << variableNumber - 1;
            variableNumber -= 2;
        }

        variableNumber++;
        file << std::endl;

    }

    file << "print(t_1)" << std::endl;
    file.close();
}