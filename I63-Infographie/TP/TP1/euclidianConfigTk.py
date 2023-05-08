from tkinter import Tk, Label, Entry, Button, messagebox
import tkUtils

class EuclidianConfigTk():
    """
    Cette classe permet de dessiner dans les fenêtres d'un window manager des polynomes et des segements.

    La definition des dimensions de l'espace mathématique se fait via:
        - x_min
        - x_max
        - y_min
        - y_max
    """

    def __init__(self, x_min=0, y_min=0, x_max=1, y_max=1, function_coefs_str="1,0,0", points_segements_str="(10,10),(18,12):(10,10),(12,18):(10,10),(18,8):(10,10),(12,2):(10,10),(2,13):(10,10),(8,2):(10,10),(2,8):(10,10),(8,20)", points_bezier="(0,0):(0,1):(1,1):(1,0)"):
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

        label_points_bezier = Label(self.root, text="Points de la courbe de Bezier")
        label_points_bezier.pack()
        self.entry_points_bezier = Entry(self.root)
        self.entry_points_bezier.insert(0, points_bezier)
        self.entry_points_bezier.pack()
        button_draw_points_bezier = Button(self.root, text="Dessiner points bezier", command=self.add_bezier_control_points)
        button_draw_points_bezier.pack()
        button_draw_curve_bezier = Button(self.root, text="Dessiner courbe bezier", command=self.draw_bezier_curve)
        button_draw_curve_bezier.pack()

        button_clear_figures = Button(self.root, text="Supprimer", command=self.clear_figures)
        button_clear_figures.pack()

        self.root.bind("<Return>",  lambda event: self.add_screen_space_tk())

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

    def add_bezier_control_points(self):
        points = tkUtils.get_list_serialized(self.entry_points_bezier.get())
        print(f"Points are: {points}")
        for screenSpaceTk in self.window_manager.get_all_window():
            screenSpaceTk.get_bezier_viewer().add_bezier_control_points_eu(points)
            screenSpaceTk.get_bezier_viewer().draw_bezier_control_points()

    def draw_bezier_curve(self):
        for screenSpaceTk in self.window_manager.get_all_window():
            screenSpaceTk.get_bezier_viewer().draw()

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

        for geo_viewer_window in self.window_manager.get_all_window():
            geo_viewer_window.get_segements_viewer().add_segements_eu(points_segements)
            geo_viewer_window.get_segements_viewer().draw()

    def draw_polynom(self):
        """
        Prend le string dans la boite de dialogue qui lui est associée, converti le string en
        liste de nombre qui correspondent aux coefficients de la fonction polynomiale à dessiner
        et dessine la fonction dans toutes les fenêtres virtuelles du window manager.
        """
        if (self.entry_coef_poly.get() == ""):
            messagebox.showerror(title="Erreur equation", message="Veuillez entrer une équation")
            return

        all_coefs = self.__get_all_coefs_function()

        for geo_viewer_window in self.window_manager.get_all_window():
            geo_viewer_window.get_polynom_viewer().add_polynoms_eu(all_coefs)
            geo_viewer_window.get_polynom_viewer().draw()

    #   +-------------------+
    #   | Fonctions privées |
    #   +-------------------+

    def __convert_text_to_point_array(self, sentence: str) -> list:
        """
        Renvoie la liste des points contenue dans la boite à dialogue associée
        """
        points_segements = []
        sentence = sentence.replace("(", "").replace(")", "")

        for pointStr in sentence.split(":"):
            pointStrArray = pointStr.split(",")
            point1X = int(pointStrArray[0])
            point1Y = int(pointStrArray[1])
            point2X = int(pointStrArray[2])
            point2Y = int(pointStrArray[3])

            points_segements.append((point1X, point1Y))
            points_segements.append((point2X, point2Y))

        return points_segements
    
    def __get_all_coefs_function(self) -> list:
        """
        Renvoie la liste des coeficients pour
        chaque fonction 
        """
        all_coefs = []
        functions_text = self.entry_coef_poly.get().split(":")
        for function_coefs_str in functions_text:
            all_coefs.append(self.__getCoefList(function_coefs_str))
        return all_coefs


    def __getCoefList(self, coefs_str) -> list:
        """
        Récupère la coefficiens dans la boite de dialogue "Coefficients du polynome"
        et renvoie la liste des coefficients dans le même ordre
        """
        coefs = []

        coefs_str = coefs_str.split(",")
        for coef_str in coefs_str:
            coefs.append(int(coef_str))
        return coefs
