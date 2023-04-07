from tkinter import Tk, Canvas
from utils.vec2D import Vec2D
from utils.color import Color
from game.option import Option
from game.game import Game

import utils.tkUtils as tkUtils


GAME_NAME = "Wolfenstein 2.5D"

class GameFrame:

    def __init__(self, option:Option):
        self.root = Tk()
        self.root.title(GAME_NAME)
        tkUtils.place_window(self.root, option.get_window_dimensions())
        tkUtils.lock_window_dimensions(self.root, option.get_window_dimensions())

        self.canvas_game = Canvas(self.root)
        self.canvas_game.pack()

        self.game = Game()


    def run(self):
        self.root.mainloop()

    def draw_pixel(self, vec2d:Vec2D, color:Color=None):
        """
        Dessine un pixel
        """
        self.canvas_game.create_rectangle(vec2d[0], vec2d[1], vec2d[0] + 1, vec2d[1] + 1)
