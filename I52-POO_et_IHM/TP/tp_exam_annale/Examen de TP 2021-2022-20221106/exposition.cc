#include "exposition.h"

	Tableau* salle;
	int nb;

//constructeurs
Exposition::Exposition() {
    this->salle = NULL;
    this->nb = 0;
}

Exposition::Exposition(Tableau* array, int arraySize) {
    Tableau *tabs = new Tableau[arraySize];

    for (int i = 0; i < arraySize; i++) {
        tabs[i] = array[i]; // attention, redéfinition de l'opérateur = nécéssaire pour la classe tableau
                            // Si pas autorisé faire: tabs[i] = Tableau(array[i]);
    }

    this->salle = tabs;
    this->nb = arraySize;
}

Exposition::Exposition(int arraySize) {
    Tableau *tabs = new Tableau[arraySize];

    for (int i = 0; i < arraySize; i++) {
        tabs[i] = Tableau();
    }

    this->salle = tabs;
    this->nb = arraySize;
}

Exposition::Exposition(const Exposition &expo):
Exposition(expo.salle, expo.nb)
{}

Exposition::~Exposition() {
    if (this->salle != NULL) {
        delete [] this->salle;
    }
}

//Surcharge de l'opérateur =
Exposition Exposition::operator=(const Exposition &expo) {
    if (this->salle != NULL) {
        delete [] this->salle;
    }

    this->salle = new Tableau[expo.nb];
    for (int i = 0; i < expo.nb; i++) {
        this->salle[i] = expo.salle[i];
    }

    this->nb = expo.nb;
    return *this;
}
	
	
//Surcharge de +
Exposition Exposition::operator+(const Tableau &tab)const {
    Exposition expoAdd = Exposition(this->nb + 1);

    for (int i = 0; i < this->nb; i++) {
        expoAdd.salle[i] = this->salle[i];
    }

    expoAdd.salle[this->nb] = tab;  // attention, redéfinition de l'opérateur = nécéssaire pour la classe tableau
                                    // Si pas autorisé faire: tabs[i] = Tableau(array[i]);

    return expoAdd;
}

//Surcharge de l'opérateur [] : retourne le Tableau de rang i de la salle
Tableau& Exposition::operator[](int i) const {
    return this->salle[i];
} 
	
// Methode GrandFormat retourne le tableau de plus grande surface 
Tableau Exposition::GrandFormat() const {

}