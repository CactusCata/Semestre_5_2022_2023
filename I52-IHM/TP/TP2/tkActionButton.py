from tkinter import Frame, Button, Toplevel, Label

class TkActionButton:

# Utiliser https://www.programcreek.com/python/example/88587/tkinter.messagebox.askyesnocancel

    def __init__(self, root, text, command):
        self.root = root

        # Dimensions de la fenêtre
        dimX = 400
        dimY = 300

        # Propriétés de la fenêtre
        self.windowsAction = Toplevel(root)
        self.windowsAction.minsize(dimX, dimY)
        self.windowsAction.maxsize(dimX, dimY)
        self.windowsAction.title("Confirm")
        self.windowsAction.protocol("WM_DELETE_WINDOW", self.destroyWindow)
        self.command = command

        # On ajoute le text
        frameText = Frame(self.windowsAction)
        labelText = Label(frameText, text=text)
        labelText.pack()
        frameText.pack(side="top")

        # On ajoute les deux boutons "Confirmer" et "Annuler"
        frameButton = Frame(self.windowsAction)
        buttonConfirmButton = Button(frameButton, text="Confirmer", command=lambda: self.confirm())
        buttonCancelButton = Button(frameButton, text="Annuler", command=lambda: self.cancel())
        buttonConfirmButton.pack(side="left")
        buttonCancelButton.pack(side="right")
        frameButton.pack(side="top")

        root.wait_visibility(self.windowsAction)
        self.windowsAction.grab_set() # fenetre bloquante
        #root.wait_window(self.windowsAction) # attente active

        self.windowsAction.mainloop()

    def confirm(self):
        """
        Si l'utilisateur a préssé le bouton
        "confirm", alors la commande est
        executée et l'application se ferme.
        """
        self.command()
        self.destroyWindow()

    def cancel(self):
        """
        Si l'utilisateur a préssé le bouton
        "cancel", alors, l'application se
        ferme.
        """
        self.destroyWindow()

    def destroyWindow(self):
        """
        Fermeture de l'application
        """
        self.windowsAction.destroy()
