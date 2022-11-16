def sortWords(colors):
    sortedColorsNames = list(colors.keys())
    
    for i in range(len(colors) - 1):
        minIndex = i
        for j in range(i + 1, len(colors)):
            if (cmp(sortedColorsNames[j], sortedColorsNames[minIndex]) == -1):
                minIndex = j
            if (minIndex != j):
                sortedColorsNames[i], sortedColorsNames[minIndex] = sortedColorsNames[minIndex], sortedColorsNames[i]
 

    return sortedColorsNames

def cmp(u, v):
    i = 0
    while ((i < len(u)) and (i < len(v)) and (u[i] == v[i])):
        i += 1

    if ((i == len(u)) and (i == len(v))):
        return 0
    elif ((i == len(u)) or ((i < len(v)) and (ord(u[i]) < ord(v[i])))):
        return -1
    elif ((i == len(v)) or ((i < len(u)) and (ord(u[i]) > ord(v[i])))):
        return 1
    else:
        return 10

def rgbToHex(rgb):
    return f"#{int(rgb[0]):02x}{int(rgb[1]):02x}{int(rgb[2]):02x}"

if __name__ == "__main__":
    print(cmp("indianRed3", "bisque"))

    print(rgbToHex("255 26 32"))