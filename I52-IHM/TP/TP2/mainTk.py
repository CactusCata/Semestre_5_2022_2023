from tkinter import Tk, Label, StringVar, Canvas, Menubutton, Frame, Menu, Button
import tkinter as tk

class MainTk:

    def __init__(self):
        self.root = Tk()

        rootDimensions = self.setupRootGeometry(ratio=0.3)
        self.root.minsize(rootDimensions[0], rootDimensions[1])
        self.root.maxsize(rootDimensions[0], rootDimensions[1])
        self.root.title("Paint3.0")
        self.root.protocol("WM_DELETE_WINDOW", self.root.destroy)

        self.createMenu()

        self.frameDrawnArea = Frame(self.root)
        self.frameDrawnAreaDimenstions = (int(0.97 * rootDimensions[0]), int(0.80 * rootDimensions[1]))
        self.canvasDrawArea = Canvas(self.frameDrawnArea, width=self.frameDrawnAreaDimenstions[0], height=self.frameDrawnAreaDimenstions[1], bg="red")
        self.canvasDrawArea.bind("<Motion-Control-Button>", lambda eventMouse:self.mouseDraw(eventMouse))
        self.canvasDrawArea.pack()
        self.frameDrawnArea.pack(side="top", fill="x")

        self.frameInfo = Frame(self.root)
        self.textInfo = StringVar()
        self.labelInfo = Label(self.frameInfo, textvariable=self.textInfo)
        self.labelInfo.pack()
        self.frameInfo.pack(side="top")

        self.root.mainloop()

    def createMenu(self):
        self.menuFrame = Frame(self.root)

        # Add "Fichier" menu
        self.menuButtonFile = Menubutton(self.menuFrame, text="Fichier")
        self.menuFile = Menu(self.menuButtonFile, tearoff=0)
        self.menuFile.add_command(label="Nouveau", command=lambda: self.newFigure())
        self.menuFile.add_command(label="Ouvrir", command=lambda: self.openFigure())
        self.menuFile.add_command(label="Sauver", command=lambda: self.saveFigure())
        self.menuFile.add_separator()
        self.menuFile.add_command(label="Quitter", command=lambda: self.quitFigure(), state=tk.DISABLED)
        self.menuButtonFile["menu"] = self.menuFile
        self.menuButtonFile.pack(side="left")

        # Add "Help button"
        self.menuHelp = Button(self.menuFrame, text="Aide", command=lambda: self.helpMenu())
        self.menuHelp.pack(side="right", fill="x")

        # Place menu frame on top
        self.menuFrame.pack(side="top", expand=True, fill="x")

    def mouseDraw(self, event):
        print(event.x, event.y)

    def setupRootGeometry(self, ratio=0.5):
        """
        Make ideal windows geometry
        """
        screenWidth = self.root.winfo_screenwidth()
        screenHeight = self.root.winfo_screenheight()

        rootHeight = (int) (ratio * screenHeight)
        rootWidth = (int) (rootHeight * 1.618) # omg the god golden number

        # widthxheight+x+y
        self.root.geometry(f"{rootWidth}x{rootHeight}+{(screenWidth - rootWidth) // 2}+{(screenHeight - rootHeight) // 2}")
        return rootWidth, rootHeight
