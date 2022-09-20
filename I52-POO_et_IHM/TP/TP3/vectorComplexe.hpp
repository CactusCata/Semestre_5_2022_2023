#ifndef VECTOR_COMPLEXE_HPP
#define VECTOR_COMPLEXE_HPP

class vectorComplexe {

    private:
        unsigned short m_size;
        Complexe *m_complexes;

    public:
      // construction a partir d'un tableau de complexes
      VecteurComplexe (const Complexe* complexes, unsigned short size);

      // construction a partir du contenu d'un fichier
      VecteurComplexe (ifstream& fStream);

      ~VecteurComplexe();

};

#endif
