from tkinter import Tk, Label, Entry, Button, messagebox

class EuclidianConfigTk():
    """
    Cette classe permet de dessiner dans les fenêtres d'un window manager des polynomes et des segements.

    La definition des dimensions de l'espace mathématique se fait via:
        - x_min
        - x_max
        - y_min
        - y_max
    """

    def __init__(self, x_min=-10, y_min=-10, x_max=10, y_max=10, function_coefs_str="1,0,0", points_segements_str="(1,3),(5,2):(7,3),(4,4)"):
        """
        Créer une fenêtre Tkinter avec de nombreuses boites de dialogues et bouttons
        
        :param x_min: x minimal de l'espace mathématique par défaut
        :param y_min: y minimal de l'espace mathématique par défaut
        :param x_max: x maximal de l'espace mathématique par défaut
        :param y_max: y maximal de l'espace mathématique par défaut
        :param function_coefs_str: Les coefficients de la fonction polynomiale par défaut
        :param points_segements_str: string qui contient les coordonnées des points qui definissent des segements qui seront dessinés
        """
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

        label_euclidian_dim = Label(self.root, text="Mettre à jour les dimensions euclidiennes:")
        label_euclidian_dim.pack()
        button_euclidian_dim = Button(self.root, text="Update", command=self.update_euclidian_dimensions)
        button_euclidian_dim.pack()

        label_coef_poly = Label(self.root, text="Coefficients du polynome:")
        label_coef_poly.pack()
        self.entry_coef_poly = Entry(self.root)
        self.entry_coef_poly.insert(0, function_coefs_str)
        self.entry_coef_poly.pack()

        button_apply_changes = Button(self.root, text="Dessiner le polynome", command=self.draw_polynom)
        button_apply_changes.pack()

        label_segements = Label(self.root, text="Dessiner le segement")
        label_segements.pack()
        self.entry_segements = Entry(self.root)
        self.entry_segements.insert(0, points_segements_str)
        self.entry_segements.pack()

        button_draw_segements = Button(self.root, text="Dessiner les segement", command=self.draw_segement)
        button_draw_segements.pack()

        button_clear_figures = Button(self.root, text="Supprimer", command=self.clear_figures)
        button_clear_figures.pack()

        self.root.bind("<Return>", self.add_screen_space_tk)

    def set_window_manager(self, window_manager):
        self.window_manager = window_manager

    def add_screen_space_tk(self):
        """
        Créer une nouvelle fenêtre virtuelles et l'ajoute aux fenêtres du window manager
        """
        self.window_manager.add_virtual_window(50, 50, 150, 100)

    def start(self):
        """
        +----------------+
        | Partie Tkinter |
        +----------------+

        Démarre la fenêtre Tkinter de la configuration de l'espace euclidien
        """
        self.root.mainloop()

    def getRoot(self):
        """
        +----------------+
        | Partie Tkinter |
        +----------------+

        Renvoie l'instance de root
        """
        return self.root

    def clear_figures(self):
        """
        Nettoie chaque fenetre du window manager 
        """
        for screenSpaceTk in self.window_manager.get_all_window():
            screenSpaceTk.clear_figures()

    def update_euclidian_dimensions(self):
        """
        Appelée lorsque l'utilisateur souhaite mettre à jour les coorodonnées
        de l'espace euclidien
        """
        min_x = int(self.entry_min_x.get())
        min_y = int(self.entry_min_y.get())
        max_x = int(self.entry_max_x.get())
        max_y = int(self.entry_max_y.get())
        for virtual_window in self.window_manager.get_all_window():
            virtual_window.euclidian_space_dim_changed(min_x, min_y, max_x, max_y)

    def draw_segement(self):
        """
        Prend le string dans la boite de dialogue qui lui est associée, converti le string en
        liste de point puis dessine une ligne entre chaque pair de point.
        """
        if (self.entry_segements.get() == ""):
            messagebox.showerror(title="Erreur segement", message="Veuillez entrer deux points")
            return

        points_segements = self.__convert_text_to_point_array(self.entry_segements.get())

        for screenSpaceTk in self.window_manager.get_all_window():
            for point_seg in points_segements:
                screenSpaceTk.add_segement(point_seg[0], point_seg[1])

    def draw_polynom(self):
        """
        Prend le string dans la boite de dialogue qui lui est associée, converti le string en
        liste de nombre qui correspondent aux coefficients de la fonction polynomiale à dessiner
        et dessine la fonction dans toutes les fenêtres virtuelles du window manager.
        """
        if (self.entry_coef_poly.get() == ""):
            messagebox.showerror(title="Erreur equation", message="Veuillez entrer une équation")
            return

        function_coefs = self.__getCoefList()

        for screenSpaceTk in self.window_manager.get_all_window():
            screenSpaceTk.add_polynom(function_coefs)

    #   +-------------------+
    #   | Fonctions privées |
    #   +-------------------+

    def __convert_text_to_point_array(self, sentence: str) -> list:
        """
        Renvoie la liste des points contenue dans la boite à dialogue associée
        """
        points_segements = []

        for pointStr in sentence.split(":"):
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

    def __getCoefList(self) -> list:
        """
        Récupère la coefficiens dans la boite de dialogue "Coefficients du polynome"
        et renvoie la liste des coefficients dans le même ordre
        """
        coefs = []

        function_text = self.entry_coef_poly.get()
        coefs_str = function_text.split(",")
        for coef_str in coefs_str:
            coefs.append(int(coef_str))
        return coefs