#include "ecue.hpp"

Ecue::Ecue():
Filiere()
{
this->intitule = "?";
this->repartition[0] = Modalite();
this->repartition[1] = Modalite();
this->repartition[2] = Modalite();
}

Ecue::Ecue(std::string discipline, std::string diplome, int niveau, std::string intitule, Modalite repartition[3]):
Filiere(discipline, diplome, niveau)
{
this->intitule = intitule;
this->repartition[0] = repartition[0];
this->repartition[1] = repartition[1];
this->repartition[2] = repartition[2];
}

Ecue::Ecue(const Ecue &ecue):
Filiere(*this)
{
this->intitule = ecue.intitule;
this->repartition[0] = ecue.repartition[0];
this->repartition[1] = ecue.repartition[1];
this->repartition[2] = ecue.repartition[2];
}

std::string Ecue::Get_intitule() const {
    return this->intitule;
}

Modalite* Ecue::Get_repartition() {
    return this->repartition;
}

std::ostream& operator<<(std::ostream &stream, const Ecue &ecue) {
    Modalite cm = ecue.repartition[0];
    Modalite tp = ecue.repartition[1];
    Modalite td = ecue.repartition[2];
    return stream << "Discipline: " << ecue.Get_discipline() 
                << ", Diplome: " << ecue.Get_diplome()
                << ", Niveau: " << ecue.Get_niveau()
                << ", Intitulé: " << ecue.Get_intitule()
                << ", répartition: " 
                << "CM: [" << cm.Get_he() << "h," << cm.Get_capacite() << " personnes, " << cm.Get_distanciel() << "],"
                << "TD: [" << td.Get_he() << "h," << td.Get_capacite() << " personnes, " << td.Get_distanciel() << "],"
                << "TP: [" << tp.Get_he() << "h," << tp.Get_capacite() << " personnes, " << tp.Get_distanciel() << "],";
}