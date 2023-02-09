import os

def load_points_from_file(fileName: str) -> list:
    """
    Charge tous les points contenus dans un fichier
    et les renvoie sous la forme
    [
        (x_1, y_1),
        (x_2, y_2),
        ...
        (x_n, y_2)
    ]
    """
    if (not os.path.exists(fileName)):
        return []

    file = open(fileName, "r")

    points = []
    file_lines = file.readlines()
    for file_line in file_lines:
        file_line_info = file_line.rstrip().split(" ")
        px = float(file_line_info[0])
        py = float(file_line_info[1])
        points.append((px, py))

    file.close()
    return points
