class Vec2D:

    def __init__(self, x:int, y:int):
        self.vect = [x, y]

    def __getitem__(self, index:int):
        return self.vect[index]

    def __setitem__(self, index:int, value:int):
        self.vect[index] = value
