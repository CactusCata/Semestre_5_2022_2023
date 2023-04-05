from  math import log2
from typing import Dict, List

def get_french_table() -> Dict[str,float]:
    """
    Renvoie la table (dictionnaire) qui contient 
    pour toute lettre de l'alphabet français sa probabilité
    d'apparition 
    """
    table = {
        "A": 0.0871, "G": 0.0097, "M": 0.0323, "S": 0.0791, "Y": 0.0019,
        "B": 0.0094, "H": 0.0108, "N": 0.0642, "T": 0.0711, "Z": 0.0021,
        "C": 0.0316, "I": 0.0699, "O": 0.0536, "U": 0.0615,
        "D": 0.0355, "J": 0.0072, "P": 0.0304, "V": 0.0184,
        "E": 0.1784, "K": 0.0016, "Q": 0.0089, "W": 0.0004,
        "F": 0.0096, "L": 0.0568, "R": 0.0643, "X": 0.0042,
    }
    return table

def get_morse_alphabet() -> List[str]:
    return ['-', '.']

def generate_table(text:str) -> Dict[str,float]:
    to_add = 1 / len(text)
    table = {}
    for c in text:
        if c not in table.keys():
            table[c] = to_add
        else:
            table[c] += to_add

    return table

def auto_info_char(character:str, table:Dict[str,float]) -> float:
    char_proba = table[character]
    if char_proba == 0:
        return 0
    else:
        return -log2(char_proba)

def auto_info_word(word:str, table:Dict[str,float]) -> float:
    sum = 0
    for c in word:
        sum += auto_info_char(c, table)
    return sum

def entropy(table:Dict[str,float]) -> float:
    sum = 0
    for c in table.keys():
        sum += table[c] * auto_info_char(c, table)
    return sum



