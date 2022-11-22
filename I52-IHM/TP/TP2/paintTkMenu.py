from tkinter import Menubutton, Menu, Button, DISABLED, filedialog
from tkActionButton import TkActionButton
import json

class PaintTkMenu:

    def __init__(self, frame):

        # Création du conteneur d'onglet
        self.menuButtonFile = Menubutton(frame, text="Fichier")
        self.menuFile = Menu(self.menuButtonFile, tearoff=0)

        # Ajout des choix dans l'onglet Fichier
        self.menuFile.add_command(label="Nouveau", command=lambda: self.newFigure())
        self.menuFile.add_command(label="Ouvrir", command=lambda: self.openFigure())
        self.menuFile.add_command(label="Sauver", command=lambda: self.saveFigure())
        self.menuFile.add_separator()
        self.menuFile.add_command(label="Quitter", command=lambda: self.quitFigure(), state=DISABLED)

        # On ajoute le menu au menu bouton
        self.menuButtonFile["menu"] = self.menuFile
        self.menuButtonFile.pack(side="left")

        # Add "Help button"
        self.menuHelp = Button(frame, text="Aide", command=lambda: self.helpMenu())
        self.menuHelp.pack(side="right", fill="x")

        self.paintGraphics = None

    def initPaintGraphics(self, paintGraphics):
        self.paintGraphics = paintGraphics

    def newFigure(self):

        # Si l'utilisateur a déjà dessiné, lui proposer de save
        if self.paintGraphics().hasDrawn():
            TkActionButton(self.canvas.winfo_toplevel(), "Des modifications ont été apportées, voulez-vous sauvegarder ?", self.saveFigure)

        self.canvas.delete("all")


    def openFigure(self):

        # Si l'utilisateur a déjà dessiné, lui proposer de save
        if self.paintGraphics().hasDrawn():
            TkActionButton(self.canvas.winfo_toplevel(), "Des modifications ont été apportées, voulez-vous sauvegarder ?", self.saveFigure)

        # Lire le fichier
        filename = fd.askopenfilename()
        // continuer ici et faire quitFigure()


    def saveFigure(self):
        if not self.paintGraphicsHasBeenInit():
            raise ValueError("You need to register paintGraphics before all")

        if not self.paintGraphics.hasDrawn():
            print("Vous n'avez rien déssiné")
        else:
            f = asksaveasfile(initialfile = 'Untitled.graphics', defaultextension=".graphics",filetypes=[("All Files","*.*"),("Graphics file","*.graphics")])
            figures = self.paintGraphics.getTagFigure()
            figuresJsoned = json.dumps(figures)
            f.write(figuresJsoned)
            f.close()

    def quitFigure(self):
        pass
