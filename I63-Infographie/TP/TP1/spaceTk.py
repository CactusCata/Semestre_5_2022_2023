from tkinter import Tk, Canvas, Toplevel
import imageManager

# on verra souvent  `MOVE_DISTANCE_FROM_WINDOW[0]` et `-MOVE_DISTANCE_FROM_WINDOW[1]`
# parce qu'on utile un repère indirect
MOVE_DISTANCE_FROM_WINDOW = (15, 15)

MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME = 5
MIN_GAP_BETWEEN_BOUNDS = 10

MIN_ROOT_WIDTH = 200
MIN_ROOT_HEIGHT = 200

"""
note:
Quand on click gauche ca ecris et met à jour les screenSpace
"""

class SpaceTk():

    def __init__(self, master=None, tk_width_pixel=500, tk_height_pixel=400):
        tk_width_pixel = max(tk_width_pixel, MIN_ROOT_WIDTH)
        tk_height_pixel = max(tk_height_pixel, MIN_ROOT_HEIGHT)

        # Liste de tous les espaces ecran
        self.screenSpaces = []

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
        self.root.minsize(width=MIN_ROOT_WIDTH, height=MIN_ROOT_HEIGHT)
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
            return

        if (self.clicked):

            if (self.last_move_point == (-1, -1)):
                self.last_move_point = (event.x, event.y)
                return

            dx = event.x - self.last_move_point[0]
            dy = event.y - self.last_move_point[1]

            current_widget = widgets[0]

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
                if (x_cross + dx < MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME):
                    dx =  MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - x_cross
                elif (x2 - (x1 + dx) < MIN_GAP_BETWEEN_BOUNDS):
                    dx = x1 - x2 + MIN_GAP_BETWEEN_BOUNDS
                self.root_canvas_real.move(current_widget, dx, 0)
                self.root_canvas_real.coords(self.window_lines_id[1], x1 + dx, line_north_coords[1], line_north_coords[2], line_north_coords[3])
                self.root_canvas_real.coords(self.window_lines_id[2], x1 + dx, line_south_coords[1], line_south_coords[2], line_south_coords[3])
                self.root_canvas_real.move(self.img_move_id, dx, 0)

            elif current_widget == self.window_lines_id[1]: # expend vers le nord
                if (y2 + dy < MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME):
                    dy = MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - y2
                elif (y1 - (y2 + dy) < MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME):
                    dy = y2 - y1 + MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME
                self.root_canvas_real.move(current_widget, 0, dy)
                self.root_canvas_real.coords(self.window_lines_id[0], line_ouest_coords[0], y2 + dy, line_ouest_coords[2], line_ouest_coords[3])
                self.root_canvas_real.coords(self.window_lines_id[3], line_est_coords[0], y2 + dy, line_est_coords[2], line_est_coords[3])
                
            elif current_widget == self.window_lines_id[2]: # expend vers le sud
                pass
            elif current_widget == self.window_lines_id[3]: # expend vers l'est
                pass

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

    def set_window(self, x1, y1, x2, y2):
        """
        Crée une fenetre virtuelle

        (x1, y1) +-----------+
                 |           |
                 |           |
                 |           |
                 +-----------+ (x2, y2)
        """

        # Draw lines who represent the bounds of the window
        self.window_lines_id[0] = self.root_canvas_real.create_line(x1, y1, x1, y2) # Ouest
        self.window_lines_id[1] = self.root_canvas_real.create_line(x1, y1, x2, y1) # North
        self.window_lines_id[2] = self.root_canvas_real.create_line(x1, y2, x2, y2) # South
        self.window_lines_id[3] = self.root_canvas_real.create_line(x2, y1, x2, y2) # Est

        # Draw the image who move the window 
        self.img_move_id = self.root_canvas_real.create_image(x1 - MOVE_DISTANCE_FROM_WINDOW[0], y2 + MOVE_DISTANCE_FROM_WINDOW[1], image=imageManager.MOVE_LOGO_TK)

    def move_window(self, dx, dy):
        """
        Permet de déplacer la fenetre virtuelle
        """
        cross_move_coords = self.root_canvas_real.coords(self.img_move_id) # indirect bottom left
        rect_top_right = self.root_canvas_real.coords(self.window_lines_id[1])[2:4] # indirect

        rect_x1 = cross_move_coords[0]
        rect_y1 = cross_move_coords[1]
        rect_x2 = rect_top_right[0]
        rect_y2 = rect_top_right[1]

        if (rect_x1 + dx < MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME): # trop à gauche
            dx = MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - rect_x1

        if (rect_x2 + dx + MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME > self.root.winfo_width()): # trop à droite
            dx = self.root.winfo_width() - (rect_x2 + MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        if (rect_y2 + dy < MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME): # trop en haut
            dy = MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - rect_y2

        if (rect_y1 + dy + MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME > self.root.winfo_height()): # trop en bas
            dy = self.root.winfo_height() - (rect_y1 + MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        self.root_canvas_real.move(self.window_lines_id[0], dx, dy)
        self.root_canvas_real.move(self.window_lines_id[1], dx, dy)
        self.root_canvas_real.move(self.window_lines_id[2], dx, dy)
        self.root_canvas_real.move(self.window_lines_id[3], dx, dy)
        self.root_canvas_real.move(self.img_move_id, dx, dy)

    def onRootResizeEvent(self, event):
        """
        Evenement déclanché quand l'utilisateur redimensionne
        la fenetre
        """
        self.root_canvas_real.config(width=event.width, height=event.height)
        x2 = self.root_canvas_real.coords(self.window_lines_id[1])[2]
        y1 = self.root_canvas_real.coords(self.window_lines_id[0])[3]
        dx = 0
        dy = 0

        if event.width - MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME < x2:
            dx = event.width - (x2 + MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        if event.height - MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME < y1:
            dy = event.height - (y1 + MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        self.move_window(dx, dy)
        self.tk_width_pixel = event.width
        self.tk_height_pixel = event.height

    def getRoot(self):
        return self.root

    def getCanvas(self):
        return self.root_canvas_real

    def getTopLeftRect(self):
        return self.root_canvas_real.coords(self.window_lines_id[0])[0:2]

    def getBotRightRect(self):
        return self.root_canvas_real.coords(self.window_lines_id[3])[2:]