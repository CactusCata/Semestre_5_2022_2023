#include "main.hpp"

int main(int argc, char *argv[]) {

    Modalite I51CM = Modalite(mod::CM, 21, 40);
    Modalite I51TD = Modalite(mod::TP, 30, 40);
    Modalite I51TP = Modalite(mod::TD, 48, 20);

    Modalite mods[] = {I51CM, I51TD, I51TP};

    Ecue I51 = Ecue("Informatique", "Licence", 3, "Algorithmique des graphes", mods);
    Formation l3Info;
    l3Info.ajouter(I51);

    for (int i = 0; i < l3Info.Get_nbEcue(); i++) {
        std::cout << l3Info[i] << std::endl;
    }

    return 0;
}