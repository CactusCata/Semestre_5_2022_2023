from tkinter import Tk, Canvas
from utils.vec2D import Vec2D
from utils.color import Color
from game.option import Option
from game.game import Game
from entity.player import Player
from world.blockType import BlockType
from minimap.minimap import Minimap
from world.world import WORLD_DIM_X, WORLD_DIM_Y

import utils.tkUtils as tkUtils


GAME_NAME = "Wolfenstein 2.5D"

class GameFrame:

    def __init__(self, option:Option, enable_minimap=True):
        self.__root = Tk()
        self.__root.title(GAME_NAME)
        tkUtils.place_window(self.__root, option.get_window_dimensions())
        tkUtils.lock_window_dimensions(self.__root, option.get_window_dimensions())

        self.__canvas_game = Canvas(self.__root, width=option.get_window_dimensions()[0], height=option.get_window_dimensions()[1])
        self.__canvas_game.pack()

        self.__option = option
        self.__minimap = None

        self.__game = Game()

        self.__player = self.__game.get_world().spawn_player(position=Vec2D(10, 10), rotation=0)
        self.__root.bind('z', lambda event: self.move_player(Vec2D(+0, +1)))
        self.__root.bind('q', lambda event: self.move_player(Vec2D(-1, +0)))
        self.__root.bind('s', lambda event: self.move_player(Vec2D(+0, -1)))
        self.__root.bind('d', lambda event: self.move_player(Vec2D(+1, +0)))
        self.__root.bind('l', lambda event: self.rotate_player(+3))
        self.__root.bind('m', lambda event: self.rotate_player(-3))

    def run(self):
        self.__root.mainloop()

    def rotate_player(self, drotation:float):
        self.__player.add_rotation(drotation)
        self.__minimap.update_minimap_player_eyes(drotation=drotation)
        self.__minimap.draw_beams()

    def move_player(self, dxy:Vec2D):
        if self.__game.get_world().world_matrix[self.__player.get_pos()[1] + dxy[1]][self.__player.get_pos()[0] + dxy[0]] == BlockType.WALL:
            return
        
        self.__player.move(dxy)
        self.__minimap.update_minimap_player_move(dxy)
        self.__minimap.draw_beams()

    def enable_minimap(self, upleft_corner:Vec2D, downright_corner:Vec2D):
        self.__minimap = Minimap(self.__game, self.__canvas_game, upleft_corner, downright_corner)
        self.__minimap.draw_minimap()

    def draw_pixel(self, vec2d:Vec2D, color:Color=None):
        """
        Dessine un pixel
        """
        if color == None:
            self.__canvas_game.create_rectangle(vec2d[0], vec2d[1], vec2d[0] + 1, vec2d[1] + 1)
        else:
            self.__canvas_game.create_rectangle(vec2d[0], vec2d[1], vec2d[0] + 1, vec2d[1] + 1, fill=color)
