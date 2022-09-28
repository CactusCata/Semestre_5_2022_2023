##############################################
#
# scanner.py
# ----------
#
# Analyseur lexical d'expression arithmétique
#
# Nicolas Méloni
# I53 - Compilation et théorie des langages
# 02-10-2019
###############################################


'''
On utilise le lexique suivant:

NB --> [0-9]+
OP --> + | - | * | /
PO  --> (
PF  --> )
'''

def scanner(s):
    list_ul = []
    """Convertit la chaine de caracteres <s> en une liste d'unités
    léxicales de la forme (<type>, <valeur>). Retourne None en cas
    d'erreur et affiche le caractere fautif

    """
    return list_ul

if __name__ == '__main__':
    tests = [('123+-',[('NB',1),('NB',2),('NB',3),('OP','+'),('OP','-')]),
             ('(1+2)',[('PO','('),('NB',1),('OP','+'),('NB',2),('PF',')')])]
    for cas, resultat in tests:
        if scanner(cas) != resultat:
            print("Erreur cas: {}\n    sortie: {}\n  resultat: {}".format(cas, scanner(cas),resultat))
        else:
            print("ok")
