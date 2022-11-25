from tkinter import Menubutton, Menu, Button, DISABLED, filedialog
from tkActionButton import TkActionButton
import json

class PaintTkMenu:

    def __init__(self, root, frame):
        self.root = root

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
        if self.paintGraphics.graphicsHadChangedFromLastSave():
            TkActionButton(self.root, "Des modifications ont été apportées, voulez-vous sauvegarder ?", self.saveFigure)

        # Nettoie l'écran
        self.paintGraphics.clear()


    def openFigure(self):

        # Si l'utilisateur a déjà dessiné, lui proposer de save
        if self.paintGraphics.graphicsHadChangedFromLastSave():
            TkActionButton(self.root, "Des modifications ont été apportées, voulez-vous sauvegarder ?", self.saveFigure)

        # Dessine les figures du fichier choisi
        file = filedialog.askopenfile(mode="r")
        if (file is not None):
            fileFigures = json.load(file)
            self.paintGraphics.clear()
            self.paintGraphics.paint(fileFigures)
            file.close()


    def saveFigure(self):
        """
        Propose de sauvegarder dans un fichier les figures
        déssinées sur le canvas
        """

        if self.paintGraphics.graphicsHadChangedFromLastSave():
            f = filedialog.asksaveasfile(mode="w", initialfile = 'Untitled.graphics', defaultextension=".graphics",filetypes=[("All Files","*.*"),("Graphics file","*.graphics")])
            
            if (f is not None):
                figures = self.paintGraphics.getFigures()
                figuresJsoned = json.dumps(figures)
                f.write(figuresJsoned)
                f.close()
                self.paintGraphics.figuresHasBeenSaved()

    def quitFigure(self):
        # Si l'utilisateur a déjà dessiné, lui proposer de save
        if self.paintGraphics.graphicsHadChangedFromLastSave():
            print("debut")
            TkActionButton(self.root, "Des modifications ont été apportées, voulez-vous sauvegarder ?", self.saveFigure)
            print("fin")

        print("test")
        # Destruction de la fenêtre
        self.root.destroy()
        self.root.update()

        
