from hyperCube import HyperCube
from typing import List, Tuple
from random import randrange
import fileReader
import shanon

def generate(var_amount, draw_amount):
    """
    Génere une séquence de variable aleatoire
    """
    l = []
    for i in range(draw_amount):
        draw_list = []
        for j in range(var_amount):
            draw_list.append(randrange(0, 2))
        l.append(tuple(draw_list))
    return l

def reduce(XN):
    """
    Retire une variable d'une séquence de variable
    aléatoire
    """
    XN_1 = []
    for draw in XN:
        XN_1.append(draw[:-1])
    return XN_1

if __name__ == "__main__":
    
    seq = generate(3, 50)
    print(f"Sequence = {seq}")
    hc = HyperCube(sequence_of_variable=seq)
    print(hc)
    print(hc.get_entropy())

    """
    XN = fileReader.read_file_seq_alea("XN.csv")
    YN = fileReader.read_file_seq_alea("YN.csv")
    
    YN_1 = reduce(YN)
    
    print("Calcul de I(X^N;Y^N)")
    print(shanon.info_mutuelle_two_seq(XN, YN))
    print("Calcul de I(X^N -> Y^N)")
    print(shanon.info_mutuelle_dirigee(XN, YN))
    print("Calcul de I(Y^(N-1) -> X^N)")
    print(shanon.info_mutuelle_dirigee(YN_1, XN))
    print("I(X^N -> Y^N) + I(Y^(N-1) -> X^N)")
    print(shanon.info_mutuelle_dirigee(XN, YN) + shanon.info_mutuelle_dirigee(YN_1, XN))
    """
    
    
    """
    spermwhales = fileReader.read_file_cachalots_properties("trajectoires.txt")
    for spermwhale in spermwhales:
        print(spermwhale)
    """

