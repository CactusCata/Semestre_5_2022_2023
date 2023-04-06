from typing import List, Dict, Tuple
from math import log2

def print_dict(dico:Dict[Tuple,float]) -> None:
    """
    Permet d'afficher joliement des dictionnaires
    """
    print("{")
    for key, value in dico.items():
        print(f"\t{key}: {value}")
    print("}")

def transpose(matrix:List[Tuple[float]]) -> List[Tuple[float]]:
    if (len(matrix) == 0):
        return []

    result = []
    for i in range(len(matrix[0])):
        result.append([0] * len(matrix))
    for i in range(len(matrix)):
       for j in range(len(matrix[0])):
           result[j][i] = matrix[i][j]
    for i in range(len(result)):
        result[i] = tuple(result[i])
    return result

def build_hyper_cube(OBS:List[Tuple[float]]) -> Dict[Tuple,float]:
    """
    Permet de construire un hyper cube à partir
    d'une matrice d'observation

    Renvoie un dictionnaire contenant:
        - en clef: état de toutes les variables aléatoires
                    pour un réel
        - en valeur: probabilité d'apparition de cette même
                    séquence
    """
    if len(OBS) == 0:
        return dict()

    hyper_cube = {}
    nb_seq = len(OBS)

    for seq in OBS:
        if seq in hyper_cube.keys():
            hyper_cube[seq] += 1
        else:
            hyper_cube[seq] = 1

    for n in hyper_cube.keys():
        hyper_cube[n] /= nb_seq
    return hyper_cube


def reduce(hyper_cube:Dict[Tuple,float]) -> Dict[Tuple,float]:
    """
    Permet de réduire à d'une dimension l'hyper cube
    """
    if len(hyper_cube.keys()) == 0 or len(tuple(hyper_cube.keys())[0]) == 0:
        return dict()

    new_hyper_cube = {}
    for key in hyper_cube.keys():
        key_reduced = key[:-1]
        proba = hyper_cube[key]
        if key_reduced not in new_hyper_cube.keys():
            new_hyper_cube[key_reduced] = proba
        else:
            new_hyper_cube[key_reduced] += proba
    return new_hyper_cube

def entropy(probabilities:List[float]) -> float:
    """
    Calcul l'entropie de la variable aléatoire
    donnée en paramètre
    """
    s = 0
    for proba in probabilities:
        if proba != 0:
            s += proba * log2(proba)
    return -s

def join_entropy(X:List[float], hyper_cube:Dict[Tuple,float]) -> float:
    H_X = entropy(X)
    H_YX = entropy(hyper_cube.values())
    return H_X + H_YX

def select_last_var_proba(hyper_cube:Dict[Tuple,float]) -> List[float]:
    X_i = [0, 0]
    for key in hyper_cube.keys():
        index = key[-1]
        X_i[index] += hyper_cube[key]
    return X_i

def chain_rule_real(hyper_cube:Dict[Tuple,float]) -> float:
    variable_amount = len(tuple(hyper_cube.keys())[0])
    if variable_amount == 1:
        return entropy(hyper_cube.values())

    s = 0
    for seq in hyper_cube.keys():
        s += hyper_cube[seq] * log2(hyper_cube[seq])
    
    return -s

def entropy_sequence(hyper_cube:Dict[Tuple,float]) -> float:
    return entropy(hyper_cube.values())

def info_mutuelle(XN_hc, YN_hc):
    return entropy_sequence(XN_hc) + entropy_sequence(YN_hc) - 0

if __name__ == "__main__":
    XN = [
    #    X1 X2 X3 X4
        (0, 0, 1, 1), # t1
        (1, 1, 0, 0), # t2
        (0, 1, 1, 1), # t3
        (0, 1, 0, 1), # t4
        (0, 0, 1, 0), # t5
        (1, 0, 1, 1), # t6
        (1, 0, 0, 0)  # t7
    ]

    YN = [
    #    Y1 Y2 Y3 Y4
        (0, 1, 0, 1), # t1
        (1, 0, 0, 1), # t2
        (0, 0, 1, 1), # t3
        (0, 0, 1, 1), # t4
        (0, 1, 1, 0), # t5
        (1, 0, 1, 0), # t6
        (1, 0, 1, 0)  # t7
    ]

    XN_hc = build_hyper_cube(XN)
    YN_hc = build_hyper_cube(YN)
    