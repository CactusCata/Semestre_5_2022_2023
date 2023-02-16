#ifndef FILIERE_H
#define FILIERE_H

#include <iostream>

class Filiere {

    private:
        std::string discipline;
        std::string diplome;
        int niveau;

    public:
        Filiere();
        Filiere(std::string discipline, std::string diplome, int niveau);
        Filiere(const Filiere &filiere);

        std::string Get_discipline() const;
        std::string Get_diplome() const;
        int Get_niveau() const;

        void Put_discipline(std::string discipline);
        void Put_diplome(std::string diplome);
        void Put_niveau(int niveau);

};

#endif