from enum import Enum

class BlockType(Enum):

    AIR = ("AIR", ' ')
    WALL = ("WALL", '+')

    @staticmethod
    def get_block_type_from_char(block_char_representation:str):
        for block_type in BlockType:
            if block_type.value[1] == block_char_representation:
                return block_type
        return None
