from typing import List, Tuple, Dict
from math import log2

class HyperCube:

    def __init__(self, **kwargs):
        if "sequence_of_variable" in kwargs:
            self.__sequence_of_variable = kwargs["sequence_of_variable"]
            self.__hc:Dict[Tuple[int],float] = HyperCube.build_hyper_cube(self.__sequence_of_variable)
            self.__sequence_amount = len(self.__hc.keys())
            self.__variable_amount = len(self.__sequence_of_variable[0]) if self.__sequence_amount > 1 else 0
        elif "__hc" in kwargs:
            self.__hc = kwargs["__hc"]
            self.__sequence_of_variable = kwargs["__sequence_of_variable"]
            self.__sequence_amount = kwargs["__sequence_amount"]
            self.__variable_amount = kwargs["__variable_amount"]
        elif "variable" in kwargs:
            variable = kwargs["variable"]
            l = []
            for e in variable:
                l.append(e,)
            self.__hc = HyperCube.build_hyper_cube(l)
            self.__sequence_amount = len(variable)
            self.__variable_amount = 1

    def get_variable_amount(self):
        """
        Revoie le nombre de variables de la séquence de variable
        aléatoire
        """
        return self.__variable_amount
    
    def get_sequence(self):
        """
        Renvoie la séquence de variable aléatoire
        """
        return self.__sequence_of_variable
    
    def get_sequence_amount(self):
        """
        Renvoie le nombre de séquence
        """
        return self.__sequence_amount

    def append_variable(self, variable:Tuple[float]) -> None:
        """
        Ajoute une variable dans l'hypercube
        """
        new_hc_sequence_of_variable = self.__sequence_of_variable.copy()
        for i in range(len(variable)):
            new_hc_sequence_of_variable[i] += variable[i]
        self.__sequence_of_variable = new_hc_sequence_of_variable
        self.__hc = HyperCube.build_hyper_cube(new_hc_sequence_of_variable)
        self.__variable_amount += 1

    def append_sequence_of_variable(self, sequence_of_variable:List[Tuple[float]]):
        """
        Ajoute une séquence de variable aléatoire dans l'hypercube
        """
        new_hc_sequence_of_variable = self.__sequence_of_variable.copy()
        for t in range(len(sequence_of_variable)):
            for k in range(len(sequence_of_variable[t])):
                new_hc_sequence_of_variable[t] += (sequence_of_variable[t][k],)
        self.__sequence_of_variable = new_hc_sequence_of_variable
        self.__hc = HyperCube.build_hyper_cube(new_hc_sequence_of_variable)
        self.__variable_amount += len(sequence_of_variable[0])

    def reduce_variable(self, index=-1):
        """
        Permet de réduire à d'une dimension l'hyper cube
        """
        if self.__sequence_amount == 0 or self.__variable_amount == 0:
            return

        new_hyper_cube = {}
        for key in self.__hc.keys():
            if index == -1:
                key_reduced = key[:-1]
            else:
                key_reduced = key[:index] + key[index + 1:]

            proba = self.__hc[key]
            if key_reduced not in new_hyper_cube.keys():
                new_hyper_cube[key_reduced] = proba
            else:
                new_hyper_cube[key_reduced] += proba

        new_sequence = []
        for draw in self.__sequence_of_variable:
            if index == -1:
                new_sequence.append(draw[:-1])
            else:
                new_sequence.append(draw[:index] + draw[index + 1:])
        self.__sequence_of_variable = new_sequence
        self.__variable_amount -= 1
        self.__hc = new_hyper_cube

    def get_entropy(self) -> float:
        """
        Renvoie l'entropie de l'hypercube
        """
        s = 0
        for proba in self.__hc.values():
            s += proba * log2(proba)
        return -s
    
    def copy(self):
        """
        Renvoie une copie de l'hyper cube
        """
        return HyperCube(__hc=self.__hc.copy(), 
                         __sequence_of_variable=self.__sequence_of_variable.copy(),
                         __sequence_amount=self.__sequence_amount, 
                         __variable_amount=self.__variable_amount)

    def __str__(self):
        """
        Permet d'afficher joliement des dictionnaires
        """
        serialized = "{\n"
        for key, value in self.__hc.items():
            serialized += f"\t{key}: {value}\n"
        serialized += "}"
        return serialized

    @staticmethod
    def build_hyper_cube(OBS:List[Tuple[float]]) -> Dict[Tuple[int],float]:
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
    
    Y = [1, 0, 1, 0, 0, 0, 1]
    hc = HyperCube(XN)
    print(hc)
    hc.append_variable(Y)
    print(hc)

    hc.reduce_variable()
    print(hc)
    hc.reduce_variable()
    print(hc)