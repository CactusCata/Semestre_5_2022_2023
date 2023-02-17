from tkinter import Tk, Canvas, Toplevel
import imageManager
from window import Window
from geo_viewer_window import GeoViewerWindow
import window_utils

class WindowManager():

    def __init__(self, master=None, tk_width_pixel=500, tk_height_pixel=400):
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

        self.tk_width_pixel = tk_width_pixel
        self.tk_height_pixel = tk_height_pixel
        self.root.minsize(width=window_utils.MIN_ROOT_WIDTH, height=window_utils.MIN_ROOT_HEIGHT)
        self.root.geometry(f"{tk_width_pixel}x{tk_height_pixel}")

        self.canvas = Canvas(self.root, width=tk_width_pixel, height=tk_width_pixel)
        self.canvas.pack()

        self.root.bind("<Motion>", lambda event: self.onMouseMoveEvent(event))
        self.root.bind("<Button-1>", lambda event: self.onLeftClickEvent())
        self.root.bind("<ButtonRelease-1>", lambda event: self.onLeftClickReleaseEvent())
        self.root.bind("<Configure>", lambda event: self.onRootResizeEvent(event))

    def start(self):
        self.root.mainloop()

    def onMouseMoveEvent(self, event):
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
                self.windows[window_id].move_window(self.tk_width_pixel, self.tk_height_pixel, dx, dy)
                self.last_move_point = (event.x, event.y)
                return

            # User tried to expend a border of the window
            if (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_MOUVABLE_LINE)):
                if (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_WEST_LINE)):
                    self.windows[window_id].expend_window_left_line(current_widget, dx)
                elif (window_utils.have_flag(self.canvas, current_widget, window_utils.FLAG_NORTH_LINE)):
                    self.windows[window_id].expend_window_top_line(current_widget, dy)

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

    def add_virtual_window(self, x1, y1, x2, y2):
        """
        Crée une fenetre virtuelle

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
            window.on_screen_resize(self.tk_width_pixel, self.tk_height_pixel, event.width, event.height)

    def getRoot(self):
        return self.root

    def getCanvas(self):
        return self.canvas
