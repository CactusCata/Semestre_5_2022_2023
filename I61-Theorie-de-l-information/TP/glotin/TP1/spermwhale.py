from typing import List

class Spermwhale:

    def __init__(self, name:str):
        self.longitudes:List[float] = []
        self.latitudes:List[float] = []
        self.depths:List[float] = []
        self.timestamps:List[float] = []
        self.name = name

    def append(self, longitude, latitude, depth, timestamp):
        self.longitudes.append(longitude)
        self.latitudes.append(latitude)
        self.depths.append(depth)
        self.timestamps.append(timestamp)

    def __str__(self):
        return f"Nombre d'enregistrement: {len(self.longitudes)}"