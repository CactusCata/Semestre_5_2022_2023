MOVE_DISTANCE_FROM_WINDOW = (15, 15)

MIN_DISTANCE_BETWEEN_WINDOW_AND_FRAME = 5
MIN_GAP_BETWEEN_BOUNDS = 10

MIN_ROOT_WIDTH = 200
MIN_ROOT_HEIGHT = 200

CURRENT_ROOT_WIDTH = 0
CURRENT_ROOT_HEIGHT = 0

FLAG_WEST_LINE = "WEST_LINE"
FLAG_NORTH_LINE = "NORTH_LINE"
FLAG_MOUVABLE_LINE = "MOUVABLE_LINE"
FLAG_BEZIER_CONTROL_POINT = "BEZIER_CONTROL_POINT"
FLAG_IMG = "IMG"

def set_root_dimensions(width: int, height: int) -> None:
    global CURRENT_ROOT_WIDTH, CURRENT_ROOT_HEIGHT
    CURRENT_ROOT_WIDTH = width
    CURRENT_ROOT_HEIGHT = height

def convert_window_id_to_flag(id: int) -> str:
    """
    Renvoie un flag valide à stocker
    dans un ensemble de widget
    """
    return f"<{id}>"

def is_window_id(tag) -> bool:
    """
    Renvoie True si le tag est un id
    Renvoie False sinon
    """
    return tag[0] == "<" and tag[-1] == ">"

def have_flag(canvas, widget_id, flag):
    """
    Renvoie True si le widget a un flag
    Renvoie False sinon
    """
    widget_tags = canvas.gettags(widget_id)
    for tag in widget_tags:
        if tag == flag:
            return True
    return False

def get_window_id_from_widget(canvas, widget_id) -> int:
    """
    Renvoie l'identifiant de la window d'un element lui appartenant
    Renvoie -1 si le widget ne possède pas de window lui appartenant
    """
    widget_tags = canvas.gettags(widget_id)
    for tag in widget_tags:
        if is_window_id(tag):
            return int(tag[1:-1])
    return -1

def draw_segement_sc_Bresenham(xa, ya, xb, yb):
    """
    Renvoie un ensemble de coordonnées pour l'espace écran
    """
    pixels_coord = []
    dx = xb - xa
    dy = yb - ya

    if (xb < xa): # Quartier 3,4,5,6
        if (yb < ya): # Quartier 5,6
            if (-dy < -dx): # Quartier 5
                dec = -dx - 2 * -dy
                x = xa
                y = ya
                while (x >= xb):
                    pixels_coord.append((x, y))
                    if dec < 0:
                        dec += 2 * -dx
                        y -= 1
                    dec -= 2 * -dy
                    x -= 1
            else: # Quartier 6
                dec = -dy + 2 * dx
                x = xa
                y = ya
                while (y >= yb):
                    pixels_coord.append((x, y))
                    if dec < 0:
                        dec += 2 * -dy
                        x -= 1
                    dec += 2 * dx

                    y -= 1
        else: # Quartier 3,4
            if (dy < -dx): # Quartier 4
                dec = -dx - 2 * dy
                x = xa
                y = ya
                while (x >= xb):
                    pixels_coord.append((x, y))
                    if dec < 0:
                        dec += 2 * -dx
                        y += 1
                    dec -= 2 * dy
                    x -= 1
            else: # Quartier 3
                dec = dy + 2 * dx
                x = xa
                y = ya
                while (y <= yb):
                    pixels_coord.append((x, y))
                    if dec < 0:
                        dec += 2 * dy
                        x -= 1
                    dec -= 2 * -dx
                    y += 1

    else: # Quartier 1,2,7,8
        if (yb < ya): # Quartier 7,8
            if (-dy < dx): # Quartier 8
                dec = dx + 2 * dy
                x = xa
                y = ya
                while (x <= xb):
                    pixels_coord.append((x, y))
                    if dec < 0:
                        dec += 2 * dx
                        y -= 1
                    dec += 2 * dy
                    x += 1
            else: # Quartier 7
                dec = -dy + 2 * dx
                x = xa
                y = ya
                while (y >= yb):
                    pixels_coord.append((x, y))
                    if dec < 0:
                        dec -= 2 * dy
                        x += 1
                    dec -= 2 * dx
                    y -= 1

        else: # Quartier 1,2
            if (dy < dx): # Quartier 1
                dec = dx - 2 * dy
                x = xa
                y = ya
                while (x <= xb):
                    pixels_coord.append((x, y))
                    if dec < 0:
                        dec += 2 * dx
                        y += 1
                    dec -= 2 * dy
                    x += 1
            else: # Quartier 2
                dec = dy - 2 * dx
                x = xa
                y = ya
                while (y <= yb):
                    pixels_coord.append((x, y))
                    if dec < 0:
                        dec += 2 * dy
                        x += 1
                    dec -= 2 * dx
                    y += 1

    return pixels_coord

def get_safe_segement_extremities_index(pixels_set, window_extremities):
    """
    It finds the first safe pixel in a set of pixels, then it finds the first pixel on the left and on
    the right that is safe
    
    :param pixels_set: the set of pixels that we want to find the safe segment extremities for
    :param current_index: the index of the pixel we're currently on
    :param window_extremities: the extremities of the window we want to draw the segment in
    :return: The index of the left and right extremities of the segment.
    """
    n = len(pixels_set)
    current_index = n // 2
    queue = [current_index]

    # Obtain a safe point
    iteration_count = 1
    found_safe_pixel = False
    while iteration_count < n and not found_safe_pixel:
        current_index = queue.pop(0)
        current_pixel = pixels_set[current_index]
        if (window_extremities[0][0] <= current_pixel[0] < window_extremities[1][0] and
            window_extremities[0][1] <= current_pixel[1] < window_extremities[1][1]):
            found_safe_pixel = True
        
        iteration_count += 1
        delta_index = n // (1 << iteration_count) 
        
        queue.append(current_index - delta_index)
        queue.append(current_index + delta_index)

    if (not found_safe_pixel):
        return None

    
    delta_index = n // (1 << iteration_count)

    # Search the max left safe point
    max_left_pixel_index = current_index
    max_left_pixel = pixels_set[max_left_pixel_index]
    while (window_extremities[0][0] <= max_left_pixel[0] < window_extremities[1][0] and
            window_extremities[0][1] <= max_left_pixel[1] < window_extremities[1][1]):
            max_left_pixel_index -= delta_index
            max_left_pixel = pixels_set[max_left_pixel_index]

    while not((window_extremities[0][0] <= max_left_pixel[0] < window_extremities[1][0] and
            window_extremities[0][1] <= max_left_pixel[1] < window_extremities[1][1])):
        max_left_pixel_index += 1
        max_left_pixel = pixels_set[max_left_pixel_index]

    # Search the min left safe point
    max_right_pixel_index = current_index
    max_right_pixel = pixels_set[max_right_pixel_index]
    while (window_extremities[0][0] <= max_right_pixel[0] < window_extremities[1][0] and
            window_extremities[0][1] <= max_right_pixel[1] < window_extremities[1][1]):
            max_right_pixel_index += delta_index
            max_right_pixel = pixels_set[max_right_pixel_index]

    while not((window_extremities[0][0] <= max_right_pixel[0] < window_extremities[1][0] and
            window_extremities[0][1] <= max_right_pixel[1] < window_extremities[1][1])):
        max_right_pixel_index -= 1
        max_right_pixel = pixels_set[max_right_pixel_index]

    return max_left_pixel_index, max_right_pixel_index
    

    
    
if __name__ == "__main__":
    pointA = (-3*10, -1*10)
    pointB = (20*10, 10*10)
    pixels = draw_segement_sc_Bresenham(pointA[0], pointA[1], pointB[0], pointB[1])
    print(pixels)
    print(get_safe_segement_extremities_index(pixels, [[-2*10, -2*10], [2*10, 2*10]]))