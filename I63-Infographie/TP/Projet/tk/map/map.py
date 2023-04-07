from typing import List
from map.blockType import BlockType

class Map:

    def __init__(self, map_matrix:List[List[BlockType]]):
        self.map_matrix = map_matrix
