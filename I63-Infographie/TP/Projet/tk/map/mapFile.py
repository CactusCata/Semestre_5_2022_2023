import utils.fileUtils as fileUtils

from map.map import Map
from map.blockType import BlockType

def load_map_file(path:str) -> Map:
    """
    Charge une map depuis un fichier
    """
    if not fileUtils.file_exist(path):
        print(f"The file with the path \"{path}\" was not found")
        exit()

    map_matrix = []

    file_map = open(path, "r")
    file_lines = file_map.readlines()
    # For each line of file
    for file_line in file_lines:
        line_matrix = []
        # Remove the char '\n'
        file_line = file_line.rstrip()
        # For each character of the line (each char represent a bloc)
        for bloc_character in file_line:
            line_matrix.append(BlockType.get_block_type_from_char(bloc_character))
        map_matrix.append(line_matrix)

    return map_matrix
