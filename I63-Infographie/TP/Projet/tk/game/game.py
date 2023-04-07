import map.mapFile as mapFile

class Game:

    def __init__(self):
        self.map = mapFile.load_map_file("../res/maps/map.dat")
