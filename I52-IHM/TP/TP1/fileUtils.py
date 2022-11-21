import errno

def loadFile(fileName):
    """
    Renvoie le fichier dont le nom est fileName
    Stop le programme si le fichier n'existe pas ou si l'utilisateur n'a pas
        la permission de le lire
    """
    try:
        file = open(fileName)
        return file
    except IOError as err:
        # Le fichier est introuvable/n'existe pas
        if (err.errno == errno.ENOENT):
            print(f"The file \"{fileName}\" do not exist.")
            exit()
        # L'utilisateur n'est pas autorisé à lire le fichier
        elif (err.errno == errno.EACCES):
            print(f"You don't have the permission to read the file \"{fileName}\".")
            print("Try to chmod this file.")
            exit()
        # Toute autre erreur
        else:
            print(f"An error append while trying to open the file \"{fileName}\".")
            exit()

def loadColors(file):
    """
    Renvoie un dictionnaire de la forme {nom: (r, g, b)} à partir d'un fichier
    """
    colors = {}
    for line in file.readlines():
        line = normalizeLine(line)

        rgb = [0, 0, 0]
        rgbIndexWritting = 0
        colorName = ""

        # converti la ligne en colorName: [r, g, b]
        for c in line:
            if (rgbIndexWritting < 3):
                if ('0' <= c <= '9'):
                    rgb[rgbIndexWritting] *= 10
                    rgb[rgbIndexWritting] += ord(c) - ord('0')
                elif (c == ' '):
                    rgbIndexWritting += 1
                else:
                    print("Syntax error.")
                    exit()
            else:
                if (c != ' ' and c != '\n'):
                    colorName += c

        # ajoute le tuple rgb s'il n'existe pas déjà
        rgbTuple = (rgb[0], rgb[1], rgb[2])
        if (rgbTuple not in colors.values()):
            colorName = colorName.replace(" ", "").lower()
            colors[colorName] = rgbTuple

    # Affiche le dictionnaire
    for key, value in colors.items():
        print(f"{key} : {value}")

    return colors

def normalizeLine(line):
    """
    Rends plus propre une ligne
    """
    # Remplace les tabulations par des espaces
    line = line.replace("\t", " ")

    # Reduit l'espace entre deux mots d'au maximum un espace
    while "  " in line:
        line = line.replace("  ", " ")

    # Le premier character ne sera pas un espace
    if line[0] == ' ':
        return line[1:]
    else:
        return line
