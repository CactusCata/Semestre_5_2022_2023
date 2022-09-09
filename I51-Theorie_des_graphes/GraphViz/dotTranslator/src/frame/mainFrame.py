from tkinter import Canvas, Toplevel, CENTER
from frame.IFrame import IFrame
import utils.mathsUtils as mathsUtils
from frame.errorFrame import ErrorFrame
import utils.socketHelper as socketHelper

class MainFrame(IFrame):

    def __init__(self, master):
        super().__init__(master, "Dot Translator", int(240*1.618), 200)
        self.master = master
        self.canvas = Canvas(self.master, width=int(240*1.618), height=200)
        super().setClosingCallback(self.onClose)

        super().createLabel(0.5, 0.1, "Convertisseur dot", fontSize=18, anchor=CENTER)
        self.bornYearTextBox = super().createTextBox(0.5, 0.40, width=20, height=1, anchor=CENTER)
        super().createButton(0.5, 0.8, "Calculate your age", 150, 40, self.askAgeToServer, anchor=CENTER)

        super().loop()

    def askAgeToServer(self):
        """
        Envoie une requete au serveur pour le calcul
        de l'âge
        """
        bornYearTextBoxText = self.bornYearTextBox.get("1.0", "end")

        if not mathsUtils.isInt(bornYearTextBoxText):
            super().throwMessage("The year entered is incorrect", title="Error")
            return

        # Envoie de l'année de naissance au serveur
        socketHelper.sendCrypt(self.clientSocket, self.publicKeyServer, bornYearTextBoxText)
        # Réponse du serveur
        serverResponse = socketHelper.receiveCrypt(self.clientSocket, self.privateKeyClient)

        super().throwMessage(serverResponse)

    def onClose(self):
        print("main frame closed")
