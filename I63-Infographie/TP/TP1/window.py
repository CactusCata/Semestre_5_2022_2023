import window_utils
import imageManager

class Window():

    """
     Crée une fenetre virtuelle

    (x1, y1) +-----------+
             |           |
             |           |
             |           |
             +-----------+ (x2, y2)
    """

    def __init__(self, window_id, canvas, x1, y1, x2, y2):
        self.window_id = str(window_id)
        self.canvas = canvas

        self.window_lines_id = []

        # Draw lines who represent the bounds of the window
        self.window_lines_id[0] = self.canvas.create_line(x1, y1, x1, y2) # Ouest
        self.window_lines_id[1] = self.canvas.create_line(x1, y1, x2, y1) # North
        self.window_lines_id[2] = self.canvas.create_line(x1, y2, x2, y2) # South
        self.window_lines_id[3] = self.canvas.create_line(x2, y1, x2, y2) # Est

        # Draw the image who move the window 
        self.img_move_id = self.canvas.create_image(x1 - window_utils.MOVE_DISTANCE_FROM_WINDOW[0], y2 + window_utils.MOVE_DISTANCE_FROM_WINDOW[1], image=imageManager.MOVE_LOGO_TK)

        # Add tag to each item in the window
        tag = (self.window_id,)
        canvas.itemconfig(self.window_lines_id[0], tags=tag)
        canvas.itemconfig(self.window_lines_id[1], tags=tag)
        canvas.itemconfig(self.window_lines_id[2], tags=tag)
        canvas.itemconfig(self.window_lines_id[3], tags=tag)
        canvas.itemconfig(self.img_move_id, tags=tag)

    def get_window_id(self) -> str:
        return self.window_id

    def get_rect_extremities(self) -> tuple[tuple[int, int], tuple[int, int]]:
        """
        Renvoie le tuple ((x1, y1), (x2, y2)) où:
            - x1 est le x à gauche du rectangle
            - y1 est le y en haut (repère direct) du rectangle
            - x2 est le x à droite du rectangle
            - y2 est le y en bas (repère direct) du rectangle

        (x1, y1) +-----------+
                 |           |
                 |           |
                 |           |
                 +-----------+ (x2, y2)
        """
        x1y1 = self.canvas.coords(self.window_lines_id[0])[:2]
        x2y2 = self.canvas.coords(self.window_lines_id[3])[2:]
        return (x1y1, x2y2)

    def get_total_extremities(self) -> tuple[tuple[int, int], tuple[int, int]]:
        """
        Renvoie le tuple ((x1, y1), (x2, y2)) où:
            - x1 est le x à gauche du total
            - y1 est le y en haut (repère direct) du total
            - x2 est le x à droite du total
            - y2 est le y en bas (repère direct) du total

        (x1, y1) O        +-----------+
                          |           |
                          |           |
                          |           |
                          +-----------+ (x2, y2)
                   ^
                 < + >                O (x2, y2)

        """
        x1 = self.canvas.coords(self.img_move_id)[0]
        y1 = self.canvas.coords(self.window_lines_id[0])[1]
        x2 = self.canvas.coords(self.window_lines_id[3])[2]
        y2 = self.canvas.coords(self.img_move_id)[1]
        return ((x1, y1), (x2, y2))

    def on_screen_resize(self, width, height):
        rect_extremities = self.get_rect_extremities()

        x2 = rect_extremities[1][0]
        y1 = rect_extremities[0][1]
        dx = 0
        dy = 0

        if width - window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME < x2:
            dx = width - (x2 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        if height - window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME < y1:
            dy = height - (y1 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        if (dx != 0 or dy != 0):
            self.move_window(dx, dy)


    def move_window(self, root_width, root_height, dx, dy):
        """
        Permet de déplacer la fenetre virtuelle
        """

        """
        cross_move_coords = self.canvas.coords(self.img_move_id) # indirect bottom left
        rect_top_right = self.canvas.coords(self.window_lines_id[1])[2:] # indirect

        rect_x1 = cross_move_coords[0]
        rect_y1 = cross_move_coords[1]
        rect_x2 = rect_top_right[0]
        rect_y2 = rect_top_right[1]

        if (rect_x1 + dx < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME): # trop à gauche
            dx = window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - rect_x1

        if (rect_x2 + dx + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME > self.root.winfo_width()): # trop à droite
            dx = self.root.winfo_width() - (rect_x2 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        if (rect_y2 + dy < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME): # trop en haut
            dy = window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - rect_y2

        if (rect_y1 + dy + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME > self.root.winfo_height()): # trop en bas
            dy = self.root.winfo_height() - (rect_y1 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        """

        total_extremities = self.get_total_extremities()

        x1 = total_extremities[0][0]
        y1 = total_extremities[0][1]
        x2 = total_extremities[1][0]
        y2 = total_extremities[1][1]

        if (x1 + dx < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME): # trop à gauche
            dx = x1 - window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME

        elif (x2 + dx > root_width - window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME): #trop à droite
            dx = root_width - (x2 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        if (y1 + dy < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME): # trop en haut
            dy = y1 - window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME

        elif (y2 + dy > root_height - window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME): # trop en bas
            dy = root_height - (y2 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)


        self.canvas.move(self.window_id, dx, dy)
        #self.canvas.move(self.window_lines_id[0], dx, dy)
        #self.canvas.move(self.window_lines_id[1], dx, dy)
        #self.canvas.move(self.window_lines_id[2], dx, dy)
        #self.canvas.move(self.window_lines_id[3], dx, dy)
        #self.canvas.move(self.img_move_id, dx, dy)

        return (dx, dy)