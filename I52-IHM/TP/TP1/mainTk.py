import tkinter as tk
from tkinter import Button, Tk, Toplevel, Canvas, StringVar, Label, Frame, Scrollbar
import utils

class MainTk:

    def __init__(self, colors, sortedRGB):
        self.colors = colors
        self.sortedRGB = sortedRGB

        self.mainRoot = Tk()


        self.root = Toplevel(self.mainRoot)
        rootDimensions = setupRootGeometry(self.root, ratio=0.3)
        self.root.minsize(rootDimensions[0], rootDimensions[1])
        self.root.maxsize(rootDimensions[0], rootDimensions[1])
        self.root.title("Choix de la couleur")
        self.root.protocol("WM_DELETE_WINDOW", self.root.destroy)

        self.colorSelected = StringVar()
        self.labelColorSelected = Label(self.root, textvariable=self.colorSelected)
        self.labelColorSelected.pack()

        self.frameMatrix = Frame(self.root)
        self.frameMatrix.pack(expand=True, fill="both")

        self.matrixCanvasDimension = (int(0.97 * rootDimensions[0]), int(0.9 * rootDimensions[1]))
        self.matrixCanvas = Canvas(self.frameMatrix, width=self.matrixCanvasDimension[0], height=self.matrixCanvasDimension[1], bg="white")
        self.matrixCanvas.pack(side="left", fill="y")

        self.setupMatrixCanvas()

        self.matrixCanvasScrollbar = Scrollbar(self.frameMatrix, command=self.matrixCanvas.yview)
        self.matrixCanvasScrollbar.pack(side="right", fill="y")
        self.matrixCanvas.configure(scrollregion=self.matrixCanvas.bbox("all"))
        self.matrixCanvas.configure(yscrollcommand=self.matrixCanvasScrollbar.set)


        self.buttonsFrame = Frame(self.root)
        self.buttonsFrame.pack()

        self.buttonOK = Button(self.buttonsFrame, text="OK", command=lambda:self.okButton())
        self.buttonOK.pack(side="left")

        self.buttonCancel = Button(self.buttonsFrame, text="Annuler", command=lambda:self.cancelButton())
        self.buttonCancel.pack(side="left")

        self.root.mainloop()

    def setupMatrixCanvas(self, rectSizePx=30, spaceBetweenRects=10):
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
        currentColorName = self.colorSelected.get()
        if (currentColorName != ""):
            currentRGBColor = self.colors[currentColorName]
            self.mainRoot.configure(bg=utils.rgbToHex(currentRGBColor))
        
        self.root.destroy()

    def cancelButton(self):
        self.root.destroy()

    def couleurPresse(self, event=None):
        id = self.matrixCanvas.find_withtag("current")
        self.colorSelected.set(self.matrixCanvas.gettags(id)[1])


def setupRootGeometry(root, ratio=0.5):
    screenWidth = root.winfo_screenwidth()
    screenHeight = root.winfo_screenheight()

    rootHeight = (int) (ratio * screenHeight)
    rootWidth = (int) (rootHeight * 1.618)

    # widthxheight+x+y
    root.geometry(f"{rootWidth}x{rootHeight}+{(screenWidth - rootWidth) // 2}+{(screenHeight - rootHeight) // 2}")
    return rootWidth, rootHeight
