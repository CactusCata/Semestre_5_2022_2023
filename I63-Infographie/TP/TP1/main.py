from euclidianConfigTk import EuclidianConfigTk

import imageManager

if __name__ == "__main__":
    imageManager.load_images()

    euclidianConfigTk = EuclidianConfigTk(-10, -10, 10, 10)
    imageManager.load_images_tk()
    euclidianConfigTk.addScreenSpaceTk()
    euclidianConfigTk.start()