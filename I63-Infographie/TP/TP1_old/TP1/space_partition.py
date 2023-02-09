from tkinter import Canvas

class SpacePartition:

    def __init__(self, x1: int, y1: int, x2: int, y2: int) -> None:
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.lines_id = []

    def get_window_id(self) -> int:
        return self.window_id

    def get_x1(self) -> int:
        return self.x1

    def get_y1(self) -> int:
        return self.y1

    def get_x2(self) -> int:
        return self.x2

    def get_y2(self) -> int:
        return self.y2

    def is_draw(self) -> bool:
        """
        Renvoie:
            - True  si la fenêtre est dessinée
            - False si la fenêtre n'est pas déssinée
        """
        return

    def move(self, dx, dy) -> None:

        # Cancel move function if space has not
        # been draw
        if (not is_draw()):
            return

        for line_id in self.lines_id:
            tk_canvas.move(line_id, dx, dy)
        self.x1 += dx
        self.x2 += dx
        self.y1 += dy
        self.y2 += dy

    def clear(self, tk_canvas: Canvas):
        """
        Supprime les lignes de délimitation
        des bords de la partition de l'espace
        """
        for line_id in self.lines_id:
            tk_canvas.clear(line_id)
        self.lines_id.clear()

    def draw(self, tk_canvas: Canvas) -> None:
        """
        Dessine un rectangle sur l'écran (window)
        """
        self.clear(tk_canvas)
        self.lines_id.append(tk_canvas.create_line(self.x1, self.y1, self.x1, self.y2)) # ouest
        self.lines_id.append(tk_canvas.create_line(self.x1, self.y1, self.x2, self.y1)) # nord
        self.lines_id.append(tk_canvas.create_line(self.x2, self.y2, self.x1, self.y2)) # sud
        self.lines_id.append(tk_canvas.create_line(self.x2, self.y2, self.x2, self.y1)) # est

    def draw_points(self, tk_canvas: Canvas, points: list) -> None:
        """
        Dessine une liste de point
        """
        for point in points:
            tk_canvas.create_oval(point[0] + self.x1 - 1, point[1] + self.y1 - 1,
                                  point[0] + self.x1 + 1, point[1] + self.y1 + 1)
