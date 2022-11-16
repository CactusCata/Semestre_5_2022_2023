#include "tableau.h"

//constructeurs
Tableau::Tableau():
Tableau("?", "?", -1, -1.0f, -1.0f, "?", false)
{}

Tableau::Tableau(string titre, string artiste, int annee, float hauteur, float largeur, string technique, bool expose) {
    Oeuvre(titre, artiste, annee, "peinture");
    this->hauteur = hauteur;
    this->largeur = largeur;
    this->technique = technique;
    this->expose = expose;
}

Tableau::Tableau(const Tableau &tableau):
Tableau(tableau.get_titre(), tableau.get_artiste(), tableau.get_annee(), tableau.hauteur, tableau.largeur, tableau.technique, tableau.expose)
{}

//surcharge de la methode  cartel pour la classe Tableau
void Tableau::cartel() const {
    Oeuvre::cartel();
    std::cout << this << std::endl;
}

//surcharge de l'opérateur <<
std::ostream &operator <<(std::ostream &stream, const Tableau &tab) {
    return stream << ",hauteur:" << tab.hauteur << ",largeur:" << tab.largeur << ",technique:" << tab.technique;
}

//Surcharge de >
bool Tableau::operator>(const Tableau &tab) const {
    return 
}