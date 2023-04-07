from utils.vec2D import Vec2D

class Option:

    def __init__(self, window_dimensions:Vec2D, fov:int):
        self.window_dimensions = window_dimensions
        self.fov = fov

    def get_window_dimensions(self) -> Vec2D:
        return self.window_dimensions

    def get_fov(self) -> int:
        return fov
