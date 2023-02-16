==========================
= Lancement du programme =
==========================

Pour tester un programme, il est nécéssaire de le creer
dans le répertoire data/psc/

Pour obtenir le code RAM associé, il faut executer le
script launch.sh avec la commande : ./launch.sh "nom_du_psc"
/!\ ATTENTION /!\ Il ne faut pas écrire l'extension à la fin
du nom du fichier.
Vous avez aussi la possibilité d'ajouter l'option valgrind à
la fin de la ligne de commande.
3 Fuites de mémoire sont présentes mais proviennent
de Bison/Flex. On peut les supprimer avec la fonction
yylex_destroy().

===============================
= Fonctionnement du programme =
===============================

1.Analyse lexicale par Flex
2.Analyse syntaxique + création de l'arbre syntaxique abstrait par Bison
3.Evalutation de l'arbre syntaxique abstrait par la fonction codegen du fichier asa_codegen.c (processus récursif)

=============================
= Liste des fonctionnalités =
=============================

Gestion des opérations arithmétiques (operateurs.psc)
Gestion des symboles (variables.psc)
Gestion des opérations de comparaisons (comparaisons.psc)
Gestion des entrées et sorties standards (iostream.psc)
Gestion de la structure conditionnelles (conditions.psc)
Gestion de la structure de répition (doubleboucle.psc)
Gestion des tableaux (tableaux.psc)
Gestion des commentaires

========================
= Choix de conceptions =
========================

Le fichier asa.c initial a été découpé en 3 parties:
	- asa_utils.c
	- asa_codegen.c
	- asa_node_creator.c
	
============
= Exemples =
============

Les exemples se trouvent dans le dossier data/psc/


