from tkinter import Tk, Canvas, Toplevel, Menu
from geo_viewer_window import GeoViewerWindow
import window_utils

class WindowManager():

    def __init__(self, master=None, tk_width_pixel=500, tk_height_pixel=400):
        """
        Créer la fenêtre Tkinter associée au window manager, applique ses dimensions et bind des evenements.

        :param master: La fenêtre mère
        :param tk_width_pixel: La largeur de la fenêtre Tkinter en pixel
        :param tk_height_pixel: La hauteur de la fenêtre Tkinter en pixel
        """
        tk_width_pixel = max(tk_width_pixel, window_utils.MIN_ROOT_WIDTH)
        tk_height_pixel = max(tk_height_pixel, window_utils.MIN_ROOT_HEIGHT)

        # Sauvegarde l'état du curseur
        self.cursor_img_status = 0

        # Permet d'allouer un nouvel identifiant à une nouvelle window
        self.window_id = 0
        # Liste de tous les espaces ecran
        self.windows = {}

        # Vrai si l'utilisateur maintient un clic gauche, faux sinon
        self.clicked = False
        # Dernière position du curseur (utilisé pour le déplacement de la fenêtre)
        self.last_move_point = (-1, -1)

        if (master == None):
            self.root = Tk()
        else:
            self.root = Toplevel(master)

        window_utils.set_root_dimensions(tk_width_pixel, tk_height_pixel)
        self.root.minsize(width=window_utils.MIN_ROOT_WIDTH, height=window_utils.MIN_ROOT_HEIGHT)
        self.root.geometry(f"{tk_width_pixel}x{tk_height_pixel}")

        self.canvas = Canvas(self.root, width=tk_width_pixel, height=tk_width_pixel)
        self.canvas.pack()

        self.root.bind("<Motion>", lambda event: self.onMouseMoveEvent(event))
        self.root.bind("<Button-1>", lambda event: self.onLeftClickEvent())
        self.root.bind("<ButtonRelease-1>", lambda event: self.onLeftClickReleaseEvent())
        self.root.bind("<Configure>", lambda event: self.onRootResizeEvent(event))

        self.m = Menu(self.root, tearoff=0)
        self.m.add_command(label="Ajouter un point de controle", command= lambda: self.add_control_point())
        self.root.bind("<Button-3>", lambda event: self.test(event))

        self.last_pos_mouse = (0, 0)


    def test(self, event):
        self.last_pos_mouse = (event.x_root, event.y_root)
        self.m.tk_popup(event.x_root, event.y_root)

    def add_control_point(self):
        pass

    def start(self):
        """
        +----------------+
        | Partie Tkinter |
        +----------------+

        Démarre la fenêtre Tkinter de la configuration de l'espace euclidien
        """
        self.root.mainloop()

    def onMouseMoveEvent(self, event):
        """
        Evenement déclanché lorsque l'utilisateur bouge la souris
        sur l'écran
        """
        widgets = self.canvas.find_withtag("current")
        if (len(widgets) == 0):
            if (self.cursor_img_status != 0):
                self.root.config(cursor="")
                self.cursor_img_status = 0
            return

        current_widget = widgets[0]
        window_id = window_utils.get_window_id_from_widget(self.canvas, current_widget)
        if (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_IMG)):
            if (self.cursor_img_status != 1):
                self.root.config(cursor="fleur")
                self.cursor_img_status = 1
        elif (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_MOUVABLE_LINE)):
            if (self.cursor_img_status != 2):
                self.root.config(cursor="sizing")
                self.cursor_img_status = 2
        else:
            if (self.cursor_img_status != 0):
                self.root.config(cursor="")
                self.cursor_img_status = 0

        if (self.clicked):

            if (self.last_move_point == (-1, -1)):
                self.last_move_point = (event.x, event.y)
                return

            dx = event.x - self.last_move_point[0]
            dy = event.y - self.last_move_point[1]

            # User tried to move the window
            if (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_IMG)):
                self.windows[window_id].move_window(dx, dy)
                self.last_move_point = (event.x, event.y)
                return

            # User tried to expend a border of the window
            if (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_MOUVABLE_LINE)):
                if (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_WEST_LINE)):
                    self.windows[window_id].expend_window_left_line(current_widget, dx)
                elif (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_NORTH_LINE)):
                    self.windows[window_id].expend_window_top_line(current_widget, dy)
                self.last_move_point = (event.x, event.y)
                return

            # User tried to move a bezier_control_point
            if (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_BEZIER_CONTROL_POINT)):
                self.windows[window_id].move_bezier_control_point(current_widget, dx, dy)
                self.last_move_point = (event.x, event.y)
                return

            self.last_move_point = (event.x, event.y)

    def onLeftClickEvent(self):
        """
        Evenement déclanché quand l'utilisateur fait
        un clic gauche
        """
        self.clicked = True

    def onLeftClickReleaseEvent(self):
        """
        Evenement déclanché quand l'utilisateur relache
        son clic gauche
        """
        self.clicked = False
        self.last_move_point = (-1, -1)

    def get_all_window(self):
        """
        Renvoie la liste de toutes les fenêtres virtuelles du window manager
        """
        return self.windows.values()

    def add_virtual_window(self, x1: int, y1: int, x2: int, y2: int):
        """
        Ajoute une fenêtre virtuelle au window manager qui sera définit
        par les positions des pixels x1,y1,x2,y2:

        (x1, y1) +-----------+
                 |           |
                 |           |
                 |           |
                 +-----------+ (x2, y2)
        """

        new_window = GeoViewerWindow(window_utils.convert_window_id_to_flag(self.window_id), self.canvas, x1, y1, x2, y2)
        self.windows[self.window_id] = new_window
        self.window_id += 1

    def onRootResizeEvent(self, event):
        """
        Evenement déclanché quand l'utilisateur redimensionne
        la fenetre
        """
        self.canvas.config(width=event.width, height=event.height)

        for window in self.windows.values():
            window.on_screen_resize(event.width, event.height)

    def getRoot(self):
        """
        +----------------+
        | Partie Tkinter |
        +----------------+

        Renvoie l'instance de root
        """
        return self.root

    def getCanvas(self):
        """
        +----------------+
        | Partie Tkinter |
        +----------------+

        Renvoie l'instance du Canvas
        """
        return self.canvas
