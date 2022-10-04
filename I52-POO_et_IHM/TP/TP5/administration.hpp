#ifndef ADMINISTRATION_HPP
#define ADMINISTRATION_HPP

#include "personne.hpp"

class Administration {

  private:
    Personne *personnes;
    unsigned int size;
    unsigned int cursor;

  public:
    Administration(Personne *personnes, unsigned int size);
    Administration();
    Administration(const Administration &administration);
    ~Administration();

    Administration &operator =(const Administration administration);


    void initIterator();
    bool hasNext();
    Personne next();


};

#endif
