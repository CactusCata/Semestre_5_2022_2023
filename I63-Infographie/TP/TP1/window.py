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
        self.window_id = window_id
        self.canvas = canvas


        # Draw lines who represent the bounds of the window
        self.window_lines_id = []
        self.window_lines_id.append(self.canvas.create_line(x1, y1, x1, y2)) # Ouest
        self.window_lines_id.append(self.canvas.create_line(x1, y1, x2, y1)) # North
        self.window_lines_id.append(self.canvas.create_line(x1, y2, x2, y2)) # South
        self.window_lines_id.append(self.canvas.create_line(x2, y1, x2, y2)) # Est

        # Draw the image who move the window
        self.img_move_id = self.canvas.create_image(x1 - window_utils.MOVE_DISTANCE_FROM_WINDOW[0], y2 + window_utils.MOVE_DISTANCE_FROM_WINDOW[1], image=imageManager.MOVE_LOGO_TK)

        # Add tag to each item in the window
        canvas.itemconfig(self.window_lines_id[0], tags=(self.window_id, window_utils.FLAG_MOUVABLE_LINE, window_utils.FLAG_WEST_LINE))
        canvas.itemconfig(self.window_lines_id[1], tags=(self.window_id, window_utils.FLAG_MOUVABLE_LINE, window_utils.FLAG_NORTH_LINE))
        canvas.itemconfig(self.window_lines_id[2], tags=(self.window_id,))
        canvas.itemconfig(self.window_lines_id[3], tags=(self.window_id,))
        canvas.itemconfig(self.img_move_id, tags=(self.window_id, window_utils.FLAG_IMG))

    def get_window_id(self) -> str:
        return self.window_id

    def get_rect_extremities(self) -> tuple:
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

    def get_total_extremities(self) -> tuple:
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

    def on_screen_resize(self, root_width, root_height, width, height):
        total_extremities = self.get_total_extremities()

        x2 = total_extremities[1][0]
        y2 = total_extremities[1][1]
        dx = 0
        dy = 0

        if width - window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME < x2:
            dx = width - (x2 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        if height - window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME < y2:
            dy = height - (y2 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME)

        if (dx != 0 or dy != 0):
            self.move_window(root_width, root_height, dx, dy)


    def move_window(self, root_width, root_height, dx, dy):
        """
        Permet de déplacer la fenetre virtuelle
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

        return (dx, dy)

    def expend_window_left_line(self, current_widget, dx):
        x_cross = self.canvas.coords(self.img_move_id)[0]
        x1 = self.canvas.coords(self.window_lines_id[0])[0]
        x2 = self.canvas.coords(self.window_lines_id[3])[0]

        line_north_coords = self.canvas.coords(self.window_lines_id[1])
        line_south_coords = self.canvas.coords(self.window_lines_id[2])

        if (x_cross + dx < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME):
            dx = window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - x_cross
        elif (x2 - (x1 + dx) < window_utils.MIN_GAP_BETWEEN_BOUNDS):
            dx = x1 - x2 + window_utils.MIN_GAP_BETWEEN_BOUNDS
        self.canvas.move(current_widget, dx, 0)
        self.canvas.coords(self.window_lines_id[1], x1 + dx, line_north_coords[1], line_north_coords[2], line_north_coords[3])
        self.canvas.coords(self.window_lines_id[2], x1 + dx, line_south_coords[1], line_south_coords[2], line_south_coords[3])
        self.canvas.move(self.img_move_id, dx, 0)

    def expend_window_top_line(self, current_widget, dy):
        y_cross = self.canvas.coords(self.img_move_id)[1]
        y1 = self.canvas.coords(self.window_lines_id[0])[1]
        y2 = self.canvas.coords(self.window_lines_id[3])[3]

        line_ouest_coords = self.canvas.coords(self.window_lines_id[0])
        line_est_coords = self.canvas.coords(self.window_lines_id[3])

        if (y1 + dy < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME):
            dy = window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME - y1
        elif (y2 - (y1 + dy) < window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME):
            dy = y1 - y2 + window_utils.MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME
        self.canvas.move(current_widget, 0, dy)
        self.canvas.coords(self.window_lines_id[0], line_ouest_coords[0], y1 + dy, line_ouest_coords[2], line_ouest_coords[3])
        self.canvas.coords(self.window_lines_id[3], line_est_coords[0], y1 + dy, line_est_coords[2], line_est_coords[3])
