from translator.translator import ITranslator
from translator.dotInfo import DotInfo

class PythonTranslator(ITranslator):

    def __init__(self):
        super().__init__("PythonTranslator")

    def loadFrom(self, text):
        """
        Exemple:
            [('A','C'),('C','B'),('C','D'),('B','E'),('D','G'),('D','H'),('E','G'),('G','I'),('H','I'),('F','I'),('F','J'),('I','J')]
        """
        dotInfo = DotInfo()
        pairsText = text[1:-1] # remove brackets

        for pair in pairsText.split(')'):
            pair = pair.replace(',', '')
            dotInfo.append()
