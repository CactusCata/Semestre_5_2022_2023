from tkinter import Tk, Canvas, Toplevel
import imageManager
from window import Window
import window_utils

# on verra souvent  `MOVE_DISTANCE_FROM_WINDOW[0]` et `-MOVE_DISTANCE_FROM_WINDOW[1]`
# parce qu'on utile un repère indirect


"""
note:
Quand on click gauche ca ecris et met à jour les screenSpace
"""

class WindowManager():

    def __init__(self, master=None, tk_width_pixel=500, tk_height_pixel=400, callback_on_rect_expend=None):
        tk_width_pixel = max(tk_width_pixel, window_utils.MIN_ROOT_WIDTH)
        tk_height_pixel = max(tk_height_pixel, window_utils.MIN_ROOT_HEIGHT)

        self.callback_on_rect_expend = callback_on_rect_expend

        self.cursor_img_status = 0

        self.window_id = 0
        # Liste de tous les espaces ecran
        self.windows = {}

        # identifiant tkinter du rectangle représentant
        # la window dans le root 
        self.window_lines_id = [-1] * 4

        # Identifiant de l'image de déplacement de la window
        self.img_move_id = -1

        # Vrai si la window est en cours de déplacement, faux sinon
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

        self.root_canvas_real = Canvas(self.root, width=tk_width_pixel, height=tk_width_pixel)
        self.root_canvas_real.pack()

        self.root.bind("<Motion>", lambda event: self.onMouseMoveEvent(event))
        self.root.bind("<Button-1>", lambda event: self.onLeftClickEvent())
        self.root.bind("<ButtonRelease-1>", lambda event: self.onLeftClickReleaseEvent())
        self.root.bind("<Configure>", lambda event: self.onRootResizeEvent(event))

    def start(self):
        self.root.mainloop()

    def onMouseMoveEvent(self, event):
        widgets = self.root_canvas_real.find_withtag("current")
        if (len(widgets) == 0):
            if (self.cursor_img_status != 0):
                self.root.config(cursor="")
                self.cursor_img_status = 0
            return

        current_widget = widgets[0]

        if (current_widget == self.img_move_id):
            if (self.cursor_img_status != 1):
                self.root.config(cursor="fleur")
                self.cursor_img_status = 1
        elif (current_widget == self.window_lines_id[0] or current_widget == self.window_lines_id[1]):
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
            if (current_widget == self.img_move_id):
                self.move_window(dx, dy)
                self.last_move_point = (event.x, event.y)
                return

            # User tried to expend a border of the window
            cross_move_coords = self.root_canvas_real.coords(self.img_move_id)
            line_ouest_coords = self.root_canvas_real.coords(self.window_lines_id[0])
            line_north_coords = self.root_canvas_real.coords(self.window_lines_id[1])
            line_south_coords = self.root_canvas_real.coords(self.window_lines_id[2])
            line_est_coords = self.root_canvas_real.coords(self.window_lines_id[3])

            x_cross = cross_move_coords[0]
            y_cross = cross_move_coords[1]
            x1 = line_ouest_coords[2]
            y1 = line_ouest_coords[3]
            x2 = line_north_coords[2]
            y2 = line_north_coords[3]

            if current_widget == self.window_lines_id[0]: # expend vers l'ouest
                if (x_cross + dx < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME):
                    dx = window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - x_cross
                elif (x2 - (x1 + dx) < window_utils.MIN_GAP_BETWEEN_BOUNDS):
                    dx = x1 - x2 + window_utils.MIN_GAP_BETWEEN_BOUNDS
                self.root_canvas_real.move(current_widget, dx, 0)
                self.root_canvas_real.coords(self.window_lines_id[1], x1 + dx, line_north_coords[1], line_north_coords[2], line_north_coords[3])
                self.root_canvas_real.coords(self.window_lines_id[2], x1 + dx, line_south_coords[1], line_south_coords[2], line_south_coords[3])
                self.root_canvas_real.move(self.img_move_id, dx, 0)

            elif current_widget == self.window_lines_id[1]: # expend vers le nord
                if (y2 + dy < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME):
                    dy = window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - y2
                elif (y1 - (y2 + dy) < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME):
                    dy = y2 - y1 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME
                self.root_canvas_real.move(current_widget, 0, dy)
                self.root_canvas_real.coords(self.window_lines_id[0], line_ouest_coords[0], y2 + dy, line_ouest_coords[2], line_ouest_coords[3])
                self.root_canvas_real.coords(self.window_lines_id[3], line_est_coords[0], y2 + dy, line_est_coords[2], line_est_coords[3])
                
            elif current_widget == self.window_lines_id[2]: # expend vers le sud
                pass
            elif current_widget == self.window_lines_id[3]: # expend vers l'est
                pass

            self.callback_on_rect_expend()

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

    def add_window(self, x1, y1, x2, y2):
        """
        Crée une fenetre virtuelle

        (x1, y1) +-----------+
                 |           |
                 |           |
                 |           |
                 +-----------+ (x2, y2)
        """

        new_window = Window(self.window_id, self.root_canvas_real, x1, y1, x2, y2)
        self.windows[self.window_id] = new_window
        self.window_id += 1

    def onRootResizeEvent(self, event):
        """
        Evenement déclanché quand l'utilisateur redimensionne
        la fenetre
        """
        self.root_canvas_real.config(width=event.width, height=event.height)
        
        for window in self.windows.values():
            window.on_screen_resize(event.width, event.height)

    def getRoot(self):
        return self.root

    def getCanvas(self):
        return self.root_canvas_real

    def getTopLeftRect(self):
        return self.root_canvas_real.coords(self.window_lines_id[0])[0:2]

    def getBotRightRect(self):
        return self.root_canvas_real.coords(self.window_lines_id[3])[2:]