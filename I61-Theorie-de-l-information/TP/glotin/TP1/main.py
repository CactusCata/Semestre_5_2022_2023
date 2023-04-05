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
    nb_var = len(OBS[0])

    for col in OBS:
        if col in hyper_cube.keys():
            hyper_cube[col] += 1
        else:
            hyper_cube[col] = 1

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

def entropy(probabilities:List[float]):
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


def chain_rule2(XN:List[Tuple[float]]) -> float:
    # Taille de la séquence de variables
    n = len(XN)
    s = 0
    for i in range(n):
        print("wow",XN)
        X_i = XN[i] # peut être à changer (dans son ordre)
        if len(XN) > 0:
            s += join_entropy(X_i, XN) - chain_rule(XN[:-1])
        else:
            s += join_entropy(X_i, XN)
    return s

def chain_rule3(hyper_cube:List[Tuple[float]]) -> float:
    """
    S'appuie sur la propriété suivante:
        H(X^n) = sum(i, 1, n, H(X_i,X^(i - 1)) - H(X^(i - 1)))
    """
    s = 0
    reduced_hyper_cube = reduce(hyper_cube)
    for i in range(len(hyper_cube.keys())):
        if (len(tuple(hyper_cube.keys())[0])) > 1:
            s += entropy(select_last_var_proba(hyper_cube)) + entropy(reduced_hyper_cube.values()) - chain_rule3(reduced_hyper_cube)
        else:
            s += entropy(select_last_var_proba(hyper_cube)) + entropy(reduced_hyper_cube.values())
    return s


def chain_rule(hyper_cube:List[Tuple[float]]) -> float:
    """
    S'appuie sur la propriété suivante:
        H(X^n) = sum(i, 1, n, H(X_i,X^(i - 1)) - H(X^(i - 1)))
    """
    reduced_hyper_cube = reduce(hyper_cube)
    print_dict(reduced_hyper_cube)
    # Taille de la séquence de variables
    X_i = [0, 0]
    for key in hyper_cube.keys():
        index = key[-1]
        X_i[index] += hyper_cube[key]

    s = 0
    for i in range(len(hyper_cube.keys())):
        key = tuple(hyper_cube.keys())[i]
        print(f"key = {key}")
        if len(key) > 0:
            s += join_entropy(key, reduced_hyper_cube) - chain_rule(reduced_hyper_cube)
        else:
            s += join_entropy(key, reduced_hyper_cube)
    return s

if __name__ == "__main__":
    OBS_1 = [   # Real 1, 2, 3, 4, 5, 6
                (0, 1, 0, 0, 0, 1, 1), # X1
                (0, 1, 1, 1, 0, 0, 0), # X2
                (1, 0, 1, 0, 1, 1, 0), # X3
                (1, 0, 1, 1, 0, 1, 0), # X4
    ]

    OBS_1 = transpose(OBS_1)
    hyper_cube = build_hyper_cube(OBS_1)
    print_dict(hyper_cube)
    print(chain_rule3(hyper_cube))

    """
    hyper_cube_1 = build_hyper_cube(OBS_1)
    print_dict(hyper_cube_1)

    for i in range(6):
        hyper_cube_1 = reduce(hyper_cube_1)
        print_dict(hyper_cube_1)
    """
