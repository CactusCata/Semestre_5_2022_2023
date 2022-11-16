#ifndef MATIERE_HPP
#define MATIERE_HPP

#include <string>

class Matiere {

  private:
    std::string nom;

  public:
    Matiere(std::string nom);
    Matiere(const Matiere &matiere);
    Matiere();

    ~Matiere();

    Matiere &operator =(const Matiere & matiere);

};

#endif
