import os
from PIL import Image, ImageTk

MOVE_LOGO = None
MOVE_LOGO_TK = None

def load_images() -> None:
    global MOVE_LOGO

    MOVE_LOGO = load_image("./res/img/move.png", (15, 15))


def load_image(path: str, dimensions):
    if (not os.path.exists(path)):
        print(f"Le fichier \"{path}\" n'existe pas")
        return None

    img = Image.open(path)
    img = img.resize(dimensions)
    return img

def load_images_tk():
    global MOVE_LOGO_TK

    MOVE_LOGO_TK = load_image_tk(MOVE_LOGO)

def load_image_tk(img):
    return ImageTk.PhotoImage(img)