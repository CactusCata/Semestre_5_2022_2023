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

}
