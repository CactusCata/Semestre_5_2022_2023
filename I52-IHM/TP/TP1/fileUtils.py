import errno

def loadFile(fileName):
    try:
        file = open(fileName)
        return file
    except IOError as err:
        if (err.errno == errno.ENOENT):
            print(f"The file \"{fileName}\" do not exist.")
            exit()
        elif (err.errno == errno.EACCES):
            print(f"You don't have the permission to read the file \"{fileName}\".")
            print("Try to chmod this file.")
            exit()
        else:
            print(f"An error append while trying to open the file \"{fileName}\".")
            exit()

def loadColors(file):
    colors = {}
    for line in file.readlines():
        colorValueArray = [0, 0, 0]
        indexOfColor = 0
        colorName = ""
        line = normalizeLine(line)
        for c in line:
            if (indexOfColor < 3):
                if ('0' <= c <= '9'):
                    colorValueArray[indexOfColor] *= 10
                    colorValueArray[indexOfColor] += ord(c) - ord('0')
                elif (c == ' '):
                    indexOfColor += 1
                else:
                    print("Syntax error.")
                    exit()
            else:
                if (c != ' ' and c != '\n'):
                    colorName += c

        rgbTuple = (colorValueArray[0], colorValueArray[1], colorValueArray[2])
        if (rgbTuple not in colors.values()):
            colorName = colorName.replace(" ", "").lower()
            colors[colorName] = rgbTuple
    
    for key, value in colors.items():
        print(f"{key} : {value}")

    return colors

def normalizeLine(line):
    line = line.replace("\t", " ")

    while "  " in line:
        line = line.replace("  ", " ")

    if line[0] == ' ':
        return line[1:]
    else:
        return line
