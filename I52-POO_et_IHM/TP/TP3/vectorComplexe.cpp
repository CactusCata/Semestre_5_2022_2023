#include "vectorComplexe.hpp"

VectorComplexe::VectorComplexe(const Complexe* complexes, unsigned short size) {
    this->m_size = size;

    this->m_complexes = new Complexe[this->m_size];
    for (unsigned short i = 0; i < this->m_size; i++) {
        this->m_complexes[i] = complexes[i];
    }
}

// construction a partir du contenu d'un fichier
VectorComplexe::VectorComplexe(std::ifstream& iFile) {
    iFile >> this->m_size;
    this->m_complexes = new Complexe[this->m_size];
    double real, imaginary;
    std::cout << "----------------" << std::endl;
    for (unsigned int i = 0; i < this->m_size; i++) {
      iFile >> real >> imaginary;
      this->m_complexes[i] = Complexe(real, imaginary);
    }
}

VectorComplexe::~VectorComplexe() {
    delete [] this->m_complexes;
}

void VectorComplexe::print() {
    std::cout << '(';
    if (this->m_size > 0) {
        for (unsigned short i = 0; i < this->m_size - 1; i++) {
            std::cout << this->m_complexes[i] << ", ";
        }
        std::cout << this->m_complexes[this->m_size - 1];
    }
    std::cout << ')';
}

// git remote set-url origin git@github.com:username/your-repository.git
