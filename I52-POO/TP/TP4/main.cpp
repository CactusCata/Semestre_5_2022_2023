#include "main.hpp"

int main(int argc, char *argv[]) {

    Personne dorian("Grey", "Dorian", 30);
    dorian.ageing();
    dorian.print();

    Professor severus("Rogue", "Severus", 50, "titulaire");
    severus.print();

    Etudiant1 potter("Potter", "Harry", 15, 4);
    unsigned int notesPotter[] = {12, 9, 15, 14};
    potter.ajouterNotes(notesPotter);
    potter.print();
    std::cout << "Sa moyenne est: " << potter.moyenne() << "." << std::endl;

    std::cout << "--------------------------------" << std::endl;

    // TODO faire seulement faire l'exercice 2 partie 3 seulement

    Matiere matieres[4] = {Matiere("Magie", 3), Matiere("Potion", 2), Matiere("Divination", 4), Matiere("Info", 1)};
    Etudiant2 harry = Etudiant2("Potter", "Harry", 15, 4, matieres);
    harry.ajouterNotes(notesPotter);

    std::cout << "La moyenne de Harry est: " << harry.moyenne() << std::endl;
}
