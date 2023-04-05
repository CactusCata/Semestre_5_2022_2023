from coding_table import CodingTable
import info_utils
from math import log2

DEFAULT_VALUE = -1.0

class ComSystem():
    
    def __init__(self, coding_table:CodingTable):
        self.coding_table = coding_table
        
        # Débit de la source
        self.source_flow:float = DEFAULT_VALUE

        # Débit du canal source
        self.channel_source_flow = DEFAULT_VALUE

    #########################################
    #                                       #
    #   Source d'information à l'encodage   #
    #                                       #
    #########################################
    def can_encode(self) -> bool:
        """
        Premier théorème de Shanon:
        Une transmission de l'information avec un taux 
        d'erreur le plus petit possible peut être réalisée si L >= H(X)
        """
        L = self.coding_table.get_average_traduction_size()
        H = info_utils.entropy(self.coding_table.table_proba)
        return L >= H
    
    def register_source_flow(self, symb_per_sec:float) -> None:
        """
        Renseigne le débit de la source, soit le nombre de symboles
        émis par la source en 1 seconde
        """
        self.source_flow = symb_per_sec

        # Si ce n'est pas précisé, le débit du canal source
        # peut être égal au débit de la source
        if self.channel_source_flow == DEFAULT_VALUE:
            self.channel_source_flow = self.source_flow

    def get_emission_rate_source(self) -> float:
        """
        Renvoie la quantité d'information produite par
        la source
        """
        if self.source_flow == DEFAULT_VALUE:
            print(f"[Warning] ComSystem#get_emission_rate_source(): Source flow has not\
                  been registered")
            return DEFAULT_VALUE
        
        H = info_utils.entropy(self.coding_table.table_proba)
        D = self.source_flow

        return H * D
    
    #########################
    #                       #
    #   Encodage au canal   #
    #                       #
    #########################
    def register_channel_source_flow(self, channel_sym_per_sec:float) -> None:
        """
        Renseigne le début du canal source, soit le nombre de symboles
        transmis par le canal en 1 seconde
        """
        self.channel_source_flow = channel_sym_per_sec

    def get_channel_source_capacity(self) -> float:
        """
        Renvoie la capacité du canal
        """
        D = self.channel_source_flow
        N = len(self.coding_table.alphabet)
        return D * log2(N)
    
    def can_pass_channel(self) -> bool:
        """
        Renvoie:
            - True si capacité du canal est supérieure ou égale au flux de message
            - False sinon
        """
        C = self.get_channel_source_capacity()
        T = self.channel_source_flow

        return C >= T

    #############
    #           #
    #   Final   #
    #           #
    #############
    def can_transfer(self) -> bool:
        """
        Pour qu'un message puisse être transféré il est nécéssaire que:
            Le premier théorème de Shanon soit respecté: les messages puissent être encodés
            Le deuxième théorème de Shanon soit respecté: la capacité du canal doit suffisante
        """
        return self.can_encode() and self.can_pass_channel()