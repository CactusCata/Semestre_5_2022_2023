def sortWords(array):
    """
    Trie un dictionnaire de type {mot: (r, g, b)} avec comme clef de
    trie le mots
    """
    sortedArray = list(array.keys())
    n = len(array)

    for i in range(n - 1):
        minIndex = i
        for j in range(i + 1, n):
            if (cmp(sortedArray[j], sortedArray[minIndex]) == -1):
                minIndex = j
            if (minIndex != j):
                cached = sortedArray[i]
                sortedArray[i] = sortedArray[minIndex]
                sortedArray[minIndex] = cached

    return sortedArray

def cmp(u, v):
    """
    Renvoie:
        1 si u > v
        0 si u == v
        -1 si u < v
    """
    i = 0

    # Tant que les character sont égaux, on avance
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
    """
    Convertie un triplet de nombre en hexadécimal
    """
    return f"#{int(rgb[0]):02x}{int(rgb[1]):02x}{int(rgb[2]):02x}"

if __name__ == "__main__":
    print(cmp("indianRed3", "bisque"))

    print(rgbToHex("255 26 32"))
