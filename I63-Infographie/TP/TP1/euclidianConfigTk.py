from tkinter import Tk, Label, Entry, Button, messagebox
from tkinter.ttk import Separator
from geo_viewer_window import GeoViewerWindow

class EuclidianConfigTk():

    def __init__(self, x_min=-10, y_min=-10, x_max=10, y_max=10, function_coefs_str="1,0,0", points_segements_str="(1,3),(5,2):(7,3),(4,4)") -> None:

        self.root = Tk()
        self.root.geometry(f"{300}x{500}")

        self.window_manager = None

        label_min_x = Label(self.root, text="x min:")
        label_min_x.pack()
        self.entry_min_x = Entry(self.root)
        self.entry_min_x.insert(0, str(x_min))
        self.entry_min_x.pack()

        label_min_y = Label(self.root, text="y min:")
        label_min_y.pack()
        self.entry_min_y = Entry(self.root)
        self.entry_min_y.insert(0, str(y_min))
        self.entry_min_y.pack()

        label_max_x = Label(self.root, text="max x:")
        label_max_x.pack()
        self.entry_max_x = Entry(self.root)
        self.entry_max_x.insert(0, str(x_max))
        self.entry_max_x.pack()

        label_max_y = Label(self.root, text="max y:")
        label_max_y.pack()
        self.entry_max_y = Entry(self.root)
        self.entry_max_y.insert(0, str(y_max))
        self.entry_max_y.pack()

        label_coef_poly = Label(self.root, text="Coefficients du polynome:")
        label_coef_poly.pack()
        self.entry_coef_poly = Entry(self.root)
        self.entry_coef_poly.insert(0, function_coefs_str)
        self.entry_coef_poly.pack()

        button_apply_changes = Button(self.root, text="Dessiner le polynome", command=self.draw_polynom)
        button_apply_changes.pack()

        separator = Separator(self.root, orient="horizontal")
        separator.pack()

        label_segements = Label(self.root, text="Dessiner le segement")
        label_segements.pack()
        self.entry_segements = Entry(self.root)
        self.entry_segements.insert(0, points_segements_str)
        self.entry_segements.pack()

        button_draw_segements = Button(self.root, text="Dessiner les segement", command=self.draw_segement)
        button_draw_segements.pack()

        button_clear_figures = Button(self.root, text="Supprimer", command=self.clear_figures)
        button_clear_figures.pack()

        self.root.bind("<Return>", lambda event: self.addScreenSpaceTk())

    def set_window_manager(self, window_manager):
        self.window_manager = window_manager

    def addScreenSpaceTk(self):
        """
        Ajoute un espace ecran dans une autre fenetre
        """
        self.window_manager.add_virtual_window(50, 50, 150, 100)

    def start(self):
        self.root.mainloop()

    def getRoot(self):
        return self.root

    def getCoefList(self) -> list:
        coefs = []

        function_text = self.entry_coef_poly.get()
        coefs_str = function_text.split(",")
        for coef_str in coefs_str:
            coefs.append(int(coef_str))
        return coefs

    def clear_figures(self):
        for screenSpaceTk in self.window_manager.get_all_window():
            screenSpaceTk.clear_figures()

    def draw_segement(self):
        if (self.entry_segements.get() == ""):
            messagebox.showerror(title="Erreur segement", message="Veuillez entrer deux points")
            return

        points_segements = self.strToPoints(self.entry_segements.get())

        min_x = int(self.entry_min_x.get())
        min_y = int(self.entry_min_y.get())
        max_x = int(self.entry_max_x.get())
        max_y = int(self.entry_max_y.get())

        for screenSpaceTk in self.window_manager.get_all_window():
            for point_seg in points_segements:
                screenSpaceTk.draw_segement(point_seg[0], point_seg[1], min_x, min_y, max_x, max_y)

    def draw_polynom(self):
        if (self.entry_coef_poly.get() == ""):
            messagebox.showerror(title="Erreur equation", message="Veuillez entrer une équation")
            return


        min_x = int(self.entry_min_x.get())
        min_y = int(self.entry_min_y.get())
        max_x = int(self.entry_max_x.get())
        max_y = int(self.entry_max_y.get())
        function_coefs = self.getCoefList()

        for screenSpaceTk in self.window_manager.get_all_window():
            screenSpaceTk.draw_function(min_x, min_y, max_x, max_y, function_coefs)

    def strToPoints(self, sentence: str) -> list:
        points_segements = []

        for pointStr in sentence.split(":"):
            print(pointStr)
            pointStrArray = pointStr.split(",")
            point1XStr = pointStrArray[0] # (x1
            point1YStr = pointStrArray[1] # y1)
            point2XStr = pointStrArray[2] # (x2
            point2YStr = pointStrArray[3] # y2)

            point1X = int(point1XStr[1:])
            point1Y = int(point1YStr[:-1])
            point2X = int(point2XStr[1:])
            point2Y = int(point2YStr[:-1])

            if (point1X < point2X):
                points_segements.append(((point1X, point1Y), (point2X, point2Y)))
            else:
                points_segements.append(((point2X, point2Y), (point1X, point1Y)))

        return points_segements
