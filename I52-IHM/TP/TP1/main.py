import sys
import fileUtils
import utils
from mainTk import MainTk

if __name__ == "__main__":

    if (len(sys.argv) < 2):
        print(f"You need to register a filename: {sys.argv[0]} <filename>")
        exit()

    fileName = sys.argv[1]
    fileRGB = fileUtils.loadFile(fileName)
    colors = fileUtils.loadColors(fileRGB)
    fileRGB.close()

    sortedRGBNames = utils.sortWords(colors)
    mainScreen = MainTk(colors, sortedRGBNames)