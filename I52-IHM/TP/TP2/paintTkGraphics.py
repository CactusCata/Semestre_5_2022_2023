from tkinter import Canvas

DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG = None
DEFAULT_LINE_COLOR = "black"
DEFAULT_LINE_COLOR_HIGHTLIGHT = "blue"

class PaintTkGraphics:

    def __init__(self, frame, widthCanv, heightCanv, color, menu):

        self.menu = menu

        self.canvas = Canvas(frame, width=widthCanv, height=heightCanv, bg=color)
        self.canvas.bind("<Control-1>", lambda eventClick:self.ctrlClick(eventClick))
        self.canvas.bind("<Motion>", lambda eventMouse:self.mouseDraw(eventMouse))
        self.canvas.bind("<ButtonRelease-1>", lambda eventClick:self.clickRelease(eventClick))
        self.canvas.bind("<Button-1>", lambda eventClick:self.click(eventClick))
        self.canvas.pack()

        # Enregistre les derniers (x, y) dessinés pour dessiner une droite avec les prochains (x, y)
        self.xLastPos = None
        self.yLastPos = None

        # Combinaison de touche préssée
        self.button1Pressed = False

        # Bouton gauche clické
        self.clicked = False

        # Compte le nombre de figure dessiné sur le canvas
        self.figureWritten = 0

        # Tag de la derniere figure surligné
        self.lastFigureHighlightTag = DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG

        # Des figrues ont-elles été déssinés depuis la dernière sauvegarde
        self.graphicsChanged = False

    def click(self, eventClick):
        self.clicked = True

    def ctrlClick(self, eventClick):
        self.button1Pressed = True

        if not self.graphicsChanged:
            self.graphicsChanged = True

    def clickRelease(self, eventClick):
        self.button1Pressed = False
        self.clicked = False
        self.figureWritten += 1

    def mouseDraw(self, event):
        if not self.button1Pressed:

            self.xLastPos = None
            self.yLastPos = None

            ids = self.canvas.find_withtag("current")

            # S'il existe une figure sur la souris la colorier en bleu
            if (len(ids) > 0):

                # Colorie la figure poitée si elle est différente de l'ancienne
                id = ids[0] # id de l'élément sur la souris
                tags = self.canvas.gettags(id)
                tagFigure = self.getTagFigure(tags) # tag commencant par 'figure'
                if (self.lastFigureHighlightTag != tagFigure):
                    self.canvas.itemconfigure(self.lastFigureHighlightTag, fill=DEFAULT_LINE_COLOR)
                    self.canvas.itemconfigure(tagFigure, fill=DEFAULT_LINE_COLOR_HIGHTLIGHT)
                    self.lastFigureHighlightTag = tagFigure

                    currentPos = (event.x, event.y)
                    lastPos = self.canvas.coords(tagFigure)
                    print(lastPos)
                    deplacement = (lastPos[0] - currentPos[0], lastPos[1] - currentPos[1])
                    self.canvas.move(tagFigure, deplacement[0], deplacement[1])


            else:
                # Si on est sur aucune figure, remettre l'ancienne figure dans sa couleur par defaut
                if (self.lastFigureHighlightTag != DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG):
                    self.canvas.itemconfigure(self.lastFigureHighlightTag, fill=DEFAULT_LINE_COLOR)
                    self.lastFigureHighlightTag = DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG

        else:
            if (self.xLastPos is not None):
                self.menu.enableSaveButtonState()
                # Faire une polyline
                lineID = self.canvas.create_line(self.xLastPos, self.yLastPos, event.x, event.y, width=4, tags="figure" + str(self.figureWritten))

            self.xLastPos = event.x
            self.yLastPos = event.y

    def graphicsHadChangedFromLastSave(self):
        """
        Renvoie vrai si des figures ont été dessinées
        Renvoie faux si aucune figure a été déssinée
        """
        return self.graphicsChanged

    def clear(self):
        """
        Supprime tous les éléments du canvas de dessin
        """
        self.canvas.delete("all")
        self.graphicsChanged = False
        self.figureWritten = 0
        self.lastFigureHighlightTag = DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG

    def getTagFigure(self, tags):
        """
        Renvoie le tag complet de la forme "figureX" ou
        X est un entier parmis une liste de tag
        """
        n = len(tags)
        i = 0
        while (i < n) and (not tags[i].startswith("figure")):
             i += 1
        return tags[i]

    def getFigures(self):
        """
        Renvoie sous forme de dictionnaire les figures
        du canvas
        """
        figures = {}

        for i in range(self.figureWritten):
            figures[i] = []
            figureLines = self.canvas.find_withtag("figure" + str(i))
            for line in figureLines:
                figures[i].append(self.canvas.coords(line))

        return figures

    def paint(self, figures):
        """
        Dessine une liste de figure
        """
        for tagNumber, figureLinesPos in figures.items():
            tag = f"figure{tagNumber}"
            for line in figureLinesPos:
                self.canvas.create_line(line[0], line[1], line[2], line[3], width=4, tags=tag)

        self.figureWritten = len(figures.keys())
        self.graphicsChanged = False
        self.lastFigureHighlightTag = DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG

    def figuresHasBeenSaved(self):
        self.graphicsChanged = False
        self.lastFigureHighlightTag = DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG
