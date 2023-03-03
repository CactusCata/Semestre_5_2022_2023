def horner(x, coefs) -> float:
    """
    coefs = [a, b, c, d, e]
    Eval the polynom P(x) = ax^4 + bx^3 + cx^2 + dx + e
    """
    sum = coefs[0]
    for i in range(1, len(coefs)):
        sum *= x
        sum += coefs[i]
    return sum

def fromEuclidienToScreen(coords_list, min_x_eu, min_y_eu, max_x_eu, max_y_eu, min_x_sc, min_y_sc, max_x_sc, max_y_sc):
    """
    Converti un ensemble de coordonnées d'un espace mathématique en un ensemble
    de coordonnées de l'espace écran
    """
    a = min_x_eu
    b = min_y_eu
    c = max_x_eu
    d = max_y_eu
    f = min_x_sc
    g = min_y_sc
    h = max_x_sc
    j = max_y_sc

    screen_coords = []

    for x, y in coords_list:
        px = int(((x - a) * (h - f)) / (c - a) + f)
        py = int(-(((j - g) * (y - b)) / (d - b)) + j)
        screen_coords.append((px, py))

    return screen_coords
