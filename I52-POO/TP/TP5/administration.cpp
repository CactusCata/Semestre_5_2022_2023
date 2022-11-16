#include "administration.hpp"

Administration::Administration(Personne *personnes, unsigned int size) {
  this->size = size;
  this->personnes = new Personne[size];

  for (unsigned int i = 0; i < size; i++) {
    this->personnes[i] = personnes[i];
  }
  this->cursor = 0;
}

Administration::Administration() {
  this->size = 0;
  this->cursor = 0;
  this->personnes = NULL;
}

Administration::Administration(const Administration &administration):
Administration(administration.personnes, administration.size)
{

}

Administration::~Administration() {
  delete [] this->personnes;
}

Administration &Administration::operator =(const Administration administration) {
  this->cursor = administration.cursor;
  if (this != &administration) {

    if (administration.size != this->size) {
      if (administration.personnes != NULL) {
        delete [] this->personnes;
      }
      this->personnes = new Personne[administration.size];
      this->size = administration.size;
    }

    for (unsigned int i = 0; i < this->size; i++) {
      this->personnes[i] = administration.personnes[i];
    }

  }
  return *this;
}


void Administration::initIterator() {
  // ?
}

bool Administration::hasNext() {
  return this->cursor < this->size;
}

Personne Administration::next() {
  return this->personnes[this->cursor++];
}
