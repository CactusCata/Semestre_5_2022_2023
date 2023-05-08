from hyperCube import HyperCube
from typing import List, Tuple
from random import randrange

def info_mutuelle(XN:List[Tuple[float]], Y:Tuple[float]):
    """
    Calcul I(X^N;Y)
    """
    hc_XNY = HyperCube(sequence_of_variable=XN)
    hc_XNY.append_variable(Y)
    s = hc_XNY.get_entropy()

    hc_XN = hc_XNY.copy()
    hc_XN.reduce_variable()
    s -= hc_XN.get_entropy()

    hc_Y = HyperCube(variable=Y)
    s += hc_Y.get_entropy()

    return s

def info_mutuelle_two_seq(XN:List[Tuple[float]], YN:List[Tuple[float]]):
    """
    Calcul I(X^N;Y^N)
    """
    hc_XN = HyperCube(sequence_of_variable=XN)
    hc_YN = HyperCube(sequence_of_variable=YN)
    s = hc_XN.get_entropy() + hc_YN.get_entropy()
    hc_XN.append_sequence_of_variable(YN)
    s -= hc_XN.get_entropy()
    return s

def info_mutuelle_dirigee(XN:List[Tuple[float]], YN:List[Tuple[float]]):
    """
    Calcul I(X^N -> Y^N)
    """
    hc_YN = HyperCube(sequence_of_variable=YN)
    s = hc_YN.get_entropy()

    hc_XNYN = HyperCube(sequence_of_variable=XN)
    hc_XNYN.append_sequence_of_variable(YN)
    hc_XNYN_1 = hc_XNYN.copy()
    hc_XNYN_1.reduce_variable()

    for i in range(max(hc_YN.get_variable_amount() , hc_XNYN.get_variable_amount() - hc_YN.get_variable_amount())):
        s -= hc_XNYN.get_entropy()
        s += hc_XNYN_1.get_entropy()
        hc_XNYN.reduce_variable(hc_XNYN.get_variable_amount() // 2)
        hc_XNYN.reduce_variable()
        hc_XNYN_1.reduce_variable(hc_XNYN_1.get_variable_amount() // 2)
        hc_XNYN_1.reduce_variable()
        
    return s