from utils.vec2D import Vec2D
from entity.entity import Entity

class Player(Entity):

    def __init__(self, position:Vec2D, rotation:float):
        super().__init__(position, rotation)