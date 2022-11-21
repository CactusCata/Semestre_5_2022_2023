from tkinter import Button, Tk, Toplevel, Canvas, StringVar, Label, Frame, Scrollbar
import utils

class MainTk:

    def __init__(self, colors, sortedRGB):
        self.colors = colors
        self.sortedRGB = sortedRGB

        # Créé les deux fenêtres
        self.mainRoot = Tk()
        self.root = Toplevel(self.mainRoot)

        # Paramètres de la fenêtre
        rootDimensions = setupRootGeometry(self.root, ratio=0.3)
        self.root.minsize(rootDimensions[0], rootDimensions[1])
        self.root.maxsize(rootDimensions[0], rootDimensions[1])
        self.root.title("Choix de la couleur")
        self.root.protocol("WM_DELETE_WINDOW", self.root.destroy)

        # Affiche le nom de la couleur choisie
        self.colorSelected = StringVar()
        labelColorSelected = Label(self.root, textvariable=self.colorSelected)
        labelColorSelected.pack()

        # Frame qui contiendra la matrice de couleur et la scrollbar
        frameMatrix = Frame(self.root)
        frameMatrix.pack(expand=True, fill="both")

        # Créé et initialise la matrice de couleur
        self.matrixCanvasDimension = (int(0.97 * rootDimensions[0]), int(0.85 * rootDimensions[1]))
        self.matrixCanvas = Canvas(frameMatrix, width=self.matrixCanvasDimension[0], height=self.matrixCanvasDimension[1], bg="white")
        self.matrixCanvas.pack(side="left", fill="y")
        self.setupMatrixCanvas()

        # Crée la scrollbar et la lie à la matrice de couleur
        matrixCanvasScrollbar = Scrollbar(frameMatrix, command=self.matrixCanvas.yview)
        matrixCanvasScrollbar.pack(side="right", fill="y")
        self.matrixCanvas.configure(scrollregion=self.matrixCanvas.bbox("all"))
        self.matrixCanvas.configure(yscrollcommand=matrixCanvasScrollbar.set)

        # Créé la frame qui contiendra les boutons
        buttonsFrame = Frame(self.root)
        buttonsFrame.pack()

        # Créé le bouton OK
        buttonOK = Button(buttonsFrame, text="OK", command=lambda:self.okButton())
        buttonOK.pack(side="left")

        # Crée le bouton Annuler
        buttonCancel = Button(buttonsFrame, text="Annuler", command=lambda:self.cancelButton())
        buttonCancel.pack(side="left")

        # Lance la fenêtre
        self.root.mainloop()

    def setupMatrixCanvas(self, rectSizePx=10, spaceBetweenRects=3):
        """
        Créé la matrice de couleur
        """
        startDrawPxLeft = spaceBetweenRects
        startDrawPxUp = spaceBetweenRects
        rectPerLine = self.matrixCanvasDimension[0] // (rectSizePx + spaceBetweenRects)
        rectLineAmount = (len(self.sortedRGB) // rectPerLine) + 1
        for i in range(rectLineAmount):
            for j in range(rectPerLine):
                if i * rectPerLine + j < len(self.sortedRGB):
                    colorName = self.sortedRGB[i * rectPerLine + j]
                    currentRGB = self.colors[colorName]
                    leftUpCornerCoordinatesPx = (startDrawPxLeft + j * (rectSizePx + spaceBetweenRects), startDrawPxUp + i * (rectSizePx + spaceBetweenRects))
                    self.matrixCanvas.create_rectangle(leftUpCornerCoordinatesPx[0], leftUpCornerCoordinatesPx[1], leftUpCornerCoordinatesPx[0] + rectSizePx, leftUpCornerCoordinatesPx[1] + rectSizePx, fill=utils.rgbToHex(currentRGB), tags=("colorRect", colorName))
                    self.matrixCanvas.tag_bind(colorName, "<Button-1>", lambda c:self.couleurPresse(c))

    def okButton(self):
        """
        Effets du boutton OK
        """
        # Récupère le nom de la couleur
        currentColorName = self.colorSelected.get()

        # Si une couleur a été choisie, met la couleur de fond de la fenêtre
        # principale en la couleur choisie
        if (currentColorName != ""):
            currentRGBColor = self.colors[currentColorName]
            self.mainRoot.configure(bg=utils.rgbToHex(currentRGBColor))

        # Détruit la fenêtre et ses filles
        self.root.destroy()

    def cancelButton(self):
        """
        Effets du bouton CANCEL
        """
        # Détruit la fenêtre et ses filles
        self.root.destroy()

    def couleurPresse(self, event=None):
        """
        Effets de l'appuie sur une couleur
        """

        id = self.matrixCanvas.find_withtag("current")
        self.colorSelected.set(self.matrixCanvas.gettags(id)[1])


def setupRootGeometry(root, ratio=0.5):
    """
    Make ideal windows geometry
    """
    screenWidth = root.winfo_screenwidth()
    screenHeight = root.winfo_screenheight()

    rootHeight = (int) (ratio * screenHeight)
    rootWidth = (int) (rootHeight * 1.618) # omg the god golden number

    # widthxheight+x+y
    root.geometry(f"{rootWidth}x{rootHeight}+{(screenWidth - rootWidth) // 2}+{(screenHeight - rootHeight) // 2}")
    return rootWidth, rootHeight
