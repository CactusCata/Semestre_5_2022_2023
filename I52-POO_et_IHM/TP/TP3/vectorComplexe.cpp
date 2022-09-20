#include "vectorComplexe"

VecteurComplexe::VecteurComplexe(const Complexe* complexes, unsigned short size) {
    this->m_size = m_size;

    this->m_complexes = new Complexe[this->m_size];
    for (unsigned short i = 0; i < this->m_size; i++) {
        this->m_complexes[i] = complexes[i];
    }
}

// construction a partir du contenu d'un fichier
VecteurComplexe::VecteurComplexe(ifstream& fStream) {

}

VecteurComplexe::~VecteurComplexe() {
    delete [] this->m_complexes;
}
