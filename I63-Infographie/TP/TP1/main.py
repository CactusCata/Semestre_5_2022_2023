from euclidianConfigTk import EuclidianConfigTk
from windowManager import WindowManager

import imageManager

if __name__ == "__main__":
    imageManager.load_images()

    euclidianConfigTk = EuclidianConfigTk()
    imageManager.load_images_tk()
    windowManager = WindowManager(master=euclidianConfigTk.getRoot())
    euclidianConfigTk.set_window_manager(windowManager)
    windowManager.add_virtual_window(30, 30, 150, 150)
    euclidianConfigTk.start()
