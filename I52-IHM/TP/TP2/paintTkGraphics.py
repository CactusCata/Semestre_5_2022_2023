from tkinter import Canvas

DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG = None
DEFAULT_LINE_COLOR = "black"
DEFAULT_LINE_COLOR_HIGHTLIGHT = "blue"

class PaintTkGraphics:

    def __init__(self, frame, widthCanv, heightCanv, color="white"):
        self.canvas = Canvas(frame, width=widthCanv, height=heightCanv, bg=color)
        self.canvas.bind("<Control-1>", lambda eventClick:self.ctrlClick(eventClick))
        self.canvas.bind("<Motion>", lambda eventMouse:self.mouseDraw(eventMouse))
        self.canvas.bind("<ButtonRelease-1>", lambda eventClick:self.clickRelease(eventClick))
        self.canvas.pack()

        # Enregistre les derniers (x, y) dessinés pour dessiner une droite avec les prochains (x, y)
        self.xLastPos = None
        self.yLastPos = None

        # Combinaison de touche préssée
        self.button1Pressed = False

        # Compte le nombre de figure dessiné sur le canvas
        self.figureWritting = 0

        # Tag de la derniere figure surligné
        self.lastFigureHighlightTag = DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG

        # has draw on image
        self.drawn = False


    def ctrlClick(self, eventClick):
        self.button1Pressed = True

        if not self.drawn:
            self.drawn = True

    def clickRelease(self, eventClick):
        self.button1Pressed = False
        self.figureWritting += 1

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
                tagFigure = getTagFigure(tags) # tag commencant par 'figure'
                if (self.lastFigureHighlightTag != tagFigure):
                    self.canvas.itemconfigure(self.lastFigureHighlightTag, fill=DEFAULT_LINE_COLOR)
                    self.canvas.itemconfigure(tagFigure, fill=DEFAULT_LINE_COLOR_HIGHTLIGHT)
                    self.lastFigureHighlightTag = tagFigure

            else:
                # Si on est sur aucune figure, remettre l'ancienne figure dans sa couleur par defaut
                if (self.lastFigureHighlightTag != DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG):
                    self.canvas.itemconfigure(self.lastFigureHighlightTag, fill=DEFAULT_LINE_COLOR)
                    self.lastFigureHighlightTag = DEFAULT_LAST_FIGURE_HIGHLIGHT_TAG

        else:
            if (self.xLastPos is not None):
                lineID = self.canvas.create_line(self.xLastPos, self.yLastPos, event.x, event.y, width=4, tags="figure" + str(self.figureWritting))

            self.xLastPos = event.x
            self.yLastPos = event.y

    def hasDrawn(self):
        return self.drawn

    def clear(self):
        self.canvas.delete("all")

    def getTagFigure(self, tags):
        n = len(tags)
        i = 0
        while (i < n) and (not tags[i].startswith("figure")):
             i += 1
        return tags[i]

    def getFigures(self):
        figures = {}

        for i in range(self.figureWritting):
            figures[i] = []
            figureLines = self.canvas.find_withtag("figure" + str(i))
            for line in figureLines:
                figures[i].append(self.canvas.coords(line))

        return figures
