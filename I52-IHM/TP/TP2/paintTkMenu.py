from tkinter import Menubutton, Menu, Button, DISABLED, ACTIVE, filedialog
from tkPerformer import TkPerformer
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
        self.menuFile.add_command(label="Sauver", command=lambda: self.saveFigure(), state=DISABLED)
        self.menuFile.add_separator()
        self.menuFile.add_command(label="Quitter", command=lambda: self.quitFigure())

        # On ajoute le menu au menu bouton
        self.menuButtonFile["menu"] = self.menuFile
        self.menuButtonFile.pack(side="left")

        # Add "Help button"
        self.menuHelp = Button(frame, text="Aide", command=lambda: self.helpMenu())
        self.menuHelp.pack(side="right", fill="x")

        # Instance de l'objet qui gère la partie graphique
        self.paintGraphics = None

        # Nom du fichier qui contient la figure
        self.figureFileName = None


    def initPaintGraphics(self, paintGraphics):
        self.paintGraphics = paintGraphics

    def enableSaveButtonState(self):
        """
        Utilisé par la zone graphique pour activer le bouton "sauver"
        """
        self.menuFile.entryconfig("Sauver", state=ACTIVE)

    def newFigure(self):
        """
        Fonction appelée lorsque l'utilisateur appuie sur le bouton "Nouveau" du menu

        Vide la zone de dessin
        """

        # Si l'utilisateur a déjà dessiné, lui proposer de save
        if self.paintGraphics.graphicsHadChangedFromLastSave():
            TkPerformer(self.root, "Sauvegarder ?", "Des modifications ont été apportées, voulez-vous sauvegarder ?", self.saveFigure)

        # Nettoie l'écran
        self.paintGraphics.clear()
        self.menuFile.entryconfig("Sauver", state=DISABLED)


    def openFigure(self):
        """
        Fonction appelée lorsque l'utilisateur appuie sur le bouton "Ouvrir" du menu

        Charge dans la zone de dessin le fichier précisé
        """

        # Si l'utilisateur a déjà dessiné, lui proposer de save
        if self.paintGraphics.graphicsHadChangedFromLastSave():
            TkPerformer(self.root, "Sauvegarder ?", "Des modifications ont été apportées, voulez-vous sauvegarder ?", self.saveFigure)

        # Dessine les figures du fichier choisi
        file = filedialog.askopenfile(mode="r")
        if (file is not None):
            fileFigures = json.load(file)
            self.paintGraphics.clear()
            self.paintGraphics.paint(fileFigures)
            file.close()

            # sauvegarde le nom du fichier chargé pour sauvegarder
            # dessus pour les prochaines actions de sauvegarde
            self.figureFileName = file.name

            # Désactivation du button sauver
            self.menuFile.entryconfig("Sauver", state=DISABLED)


    def saveFigure(self):
        """
        Propose de sauvegarder dans un fichier les figures
        dessinées sur le canvas
        """

        if self.paintGraphics.graphicsHadChangedFromLastSave():
            f = None
            if self.figureFileName == None:
                f = filedialog.asksaveasfile(mode="w", initialfile = 'Untitled.graphics', defaultextension=".graphics",filetypes=[("All Files","*.*"),("Graphics file","*.graphics")])
                self.figureFileName = f.name
            else:
                f = open(self.figureFileName, "w")

            if (f is not None):
                figures = self.paintGraphics.getFigures()
                figuresJsoned = json.dumps(figures)
                f.write(figuresJsoned)
                f.close()
                self.paintGraphics.figuresHasBeenSaved()

                # Désactivation du button sauver
                self.menuFile.entryconfig("Sauver", state=DISABLED)

    def quitFigure(self):
        # Si l'utilisateur a déjà dessiné, lui proposer de save
        if self.paintGraphics.graphicsHadChangedFromLastSave():
            TkPerformer(self.root, "Sauvegarder ?", "Des modifications ont été apportées, voulez-vous sauvegarder ?", self.saveFigure)

        # Destruction de la fenêtre
        self.root.destroy()
