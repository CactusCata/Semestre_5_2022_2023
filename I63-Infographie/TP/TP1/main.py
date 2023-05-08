from euclidianConfigTk import EuclidianConfigTk
from windowManager import WindowManager

import imageManager

import cProfile
from pstats import Stats

import sys

def start():
    imageManager.load_images()

    euclidianConfigTk = EuclidianConfigTk()
    imageManager.load_images_tk()
    windowManager = WindowManager(master=euclidianConfigTk.getRoot())
    euclidianConfigTk.set_window_manager(windowManager)
    windowManager.add_virtual_window(30, 30, 150, 150)
    euclidianConfigTk.start()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        start()
    elif sys.argv[1] == "--debug":
        with cProfile.Profile() as pr:
            start()
        print(f"Creating profilling file...")
        stats = Stats(pr).dump_stats(filename='profiling.prof')
        print(f"Profilling file created !")
        # Pour afficher le profile, utiliser la commande $ snakeviz profilling.prof
        
    else:
        print(f"Unknow option \"{sys.argv[1]}\"")


