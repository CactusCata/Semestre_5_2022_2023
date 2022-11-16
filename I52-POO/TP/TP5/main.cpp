#include "main.hpp"

int main(int argc, char *argv[]) {

  Matiere i51("i51");
  Matiere i52("i52");
  Matiere i53("i53");
  Matiere i54("i54");
  Matiere i55("i55");

  Matiere matieresGillot[] = {i52, i51};
  Professeur gillot("Gillot", "Valérie", 40, matieresGillot, 2);

  Matiere matieresNguyen[] = {i53};
  Professeur nguyen("Nguyen", "Christian", 40, matieresNguyen, 1);

  Matiere matieresInfo[] = {i51, i52, i53, i54, i55};
  Cursus cursusInformatique("Informatique", nguyen, matieresInfo, 5);

  Etudiant alexandre("Lerousseau", "Alexandre", 7, cursusInformatique);

  std::cout << "Présentations" << std::endl;

  Personne all[] = {gillot, nguyen, alexandre};
  Administration administration(all, 3);

  while (administration.hasNext()) {
    std::cout << administration.next() << std::endl;
  }


}
