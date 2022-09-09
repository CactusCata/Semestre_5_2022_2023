import translator.translatorManager as translatorManager

class ITranslator:

    def __init__(self, name):
        self.name = name
        self.id = translatorManager.generateID()
        self.dotInfo = None

    def loadFrom(self, text):
        """
        Text need to have the best format possible:
            - Aucun espace
            - Sur une seule ligne
        """
        print(f"{self}: Function loadFrom is not defined.")

    def convertTo(self):
        print(f"{self}: Function convertTo is not defined.")

    def __str__(self):
        return f"[{self.id}] Translator '{self.name}'"
