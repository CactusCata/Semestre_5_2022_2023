from tkinter import Tk, Label, StringVar, Menubutton, Frame, Menu, Button
import tkinter as tk
from paintTkGraphics import PaintTkGraphics
from paintTkMenu import PaintTkMenu
import tkUtils

# Liste des binds: https://stackoverflow.com/questions/32289175/list-of-all-tkinter-events

class PaintTk:

    def __init__(self):
        self.root = Tk()

        # Propriétés de la fenêtre
        rootDimensions = tkUtils.setupRootGeometry(self.root, ratio=0.3)
        self.root.minsize(rootDimensions[0], rootDimensions[1])
        self.root.maxsize(rootDimensions[0], rootDimensions[1])
        self.root.title("Paint3.0")

        self.initMenuAndGraphics()

        self.root.protocol("WM_DELETE_WINDOW", self.menu.quitFigure)

        # Creation l'espace d'information courante en bas de la fenêtre
        self.frameInfo = Frame(self.root)
        self.textInfo = StringVar()
        self.labelInfo = Label(self.frameInfo, textvariable=self.textInfo)
        self.labelInfo.pack()
        self.frameInfo.pack(side="top")

        self.root.mainloop()

    def initMenuAndGraphics(self):
        # Creation du menu
        self.frameMenu = Frame(self.root)
        self.menu = PaintTkMenu(self.root, self.frameMenu)
        self.frameMenu.pack(side="top", expand=True, fill="x")


        # Creation de l'interface de dessin
        self.frameDrawnArea = Frame(self.root)
        frameDrawnAreaDimenstions = (int(0.97 * self.root.winfo_screenwidth()), int(0.80 * self.root.winfo_screenheight()))
        self.paintGraphics = PaintTkGraphics(self.frameDrawnArea, frameDrawnAreaDimenstions[0], frameDrawnAreaDimenstions[1], "red")
        self.frameDrawnArea.pack(side="top")

        # Connecte la zone graphique au menu
        self.menu.initPaintGraphics(self.paintGraphics)
