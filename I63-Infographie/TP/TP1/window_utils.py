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
