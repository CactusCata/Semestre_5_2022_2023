#include "oeuvre.h"

Oeuvre::Oeuvre():
Oeuvre("?", "?", -1, "")
{}

Oeuvre::Oeuvre(string titre, string artiste, int annee, string art) {
    this->titre = titre;
    this->artiste = artiste;
    this->annee = annee;
    this->art = art;
}

Oeuvre::Oeuvre(const Oeuvre &oeuvre)
{
    this->titre = oeuvre.titre;
    this->artiste = oeuvre.artiste;
    this->annee = oeuvre.annee;
    this->art = oeuvre.art;
}

//accesseurs
string Oeuvre::get_titre()const {
    return this->titre;
}

string Oeuvre::get_artiste()const {
    return this->artiste;
}

int Oeuvre::get_annee()const {
    return this->annee;
}

string Oeuvre::get_art()const {
    return this->art;
}

//methode
void Oeuvre::cartel()const {
    std::cout << "titre:" << this->get_titre() << ",artiste:" << this->get_artiste() << ",annee:" << this->get_annee() << ",art:" << this->get_art() << std::endl;
}