#ifndef VECTOR_COMPLEXE_HPP
#define VECTOR_COMPLEXE_HPP

#include "complexe.hpp"
#include <fstream>

class VectorComplexe {

    private:
        unsigned short m_size;
        Complexe *m_complexes;

    public:
      // construction a partir d'un tableau de complexes
      VectorComplexe (const Complexe* complexes, unsigned short size);

      // construction a partir du contenu d'un fichier
      VectorComplexe (std::ifstream& fStream);

      ~VectorComplexe();

      void print();

};

#endif
