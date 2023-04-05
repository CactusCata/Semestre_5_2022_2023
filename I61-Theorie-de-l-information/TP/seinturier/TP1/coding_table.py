from typing import Dict
import utils
import info_utils

class CodingTable:

    def __init__(self, translation_table:Dict[str,str], alphabet=None):
        self.translation_table_A = translation_table
        self.translation_table_B = utils.create_reverse_dict(self.translation_table_A)
        self.alphabet = alphabet

        self.table_proba = None

    def need_table_proba(func):
        def wrapper(self):
            if self.table_proba == None:
                raise ValueError("You need to init the proba table first")
            return func(self)
        return wrapper

    def translate_A_to_B(self, word:str) -> str:
        return self.translation_table_A[word]
    
    def translate_B_to_A(self, word:str) -> str:
        return self.translate_B_to_A[word]
    
    def get_traduction_size(self, word) -> int:
        return len(self.translate_A_to_B(word))
    
    def proba_table_is_init(self) -> bool:
        return self.table_proba != None
    
    def register_proba_table(self, table_proba:Dict[str,float]) -> None:
        self.table_proba = table_proba
    
    @need_table_proba
    def get_average_traduction_size(self) -> float:
        sum = 0
        for word in self.translation_table_A.keys():
            sum += self.table_proba[word] * self.get_traduction_size(word)
        return sum
        