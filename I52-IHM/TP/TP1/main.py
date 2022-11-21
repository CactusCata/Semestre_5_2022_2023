import sys
import fileUtils
import utils
from mainTk import MainTk

if (len(sys.argv) < 2):
    print(f"You need to register a filename: {sys.argv[0]} <filename>")
    exit()

# Converti le fichier en dictionnaire de {nom, (r, g, b)}
fileName = sys.argv[1]
fileRGB = fileUtils.loadFile(fileName)
colors = fileUtils.loadColors(fileRGB)
fileRGB.close()

# Trie les noms du dictionnaire
sortedRGBNames = utils.sortWords(colors)

# Lance la fenêtre
mainScreen = MainTk(colors, sortedRGBNames)
