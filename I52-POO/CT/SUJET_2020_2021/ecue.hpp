#ifndef ECUE_H
#define ECUE_H

#include <iostream>
#include "filiere.hpp"
#include "modalite.hpp"

class Ecue : public Filiere {

    private:
        std::string intitule;
        Modalite repartition[3];

    public:
        Ecue();
        Ecue(std::string discipline, std::string diplome, int niveau, std::string intitule, Modalite repartition[3]);
        Ecue(const Ecue &ecue);

        std::string Get_intitule() const;
        Modalite* Get_repartition();

        friend std::ostream& operator<<(std::ostream &stream, const Ecue &ecue); 
};

#endif