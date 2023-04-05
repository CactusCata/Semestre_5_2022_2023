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

def binomial_coef(k, n):
    product = 1
    for i in range(1, k + 1):
        product *= ((n + 1 - i) / i)
    return int(product)

def step1(n):
    coefs = [0] * (n + 1)
    for k in range(n + 1):
        a = binomial_coef(k, n)
        if (k & 1):
            a *= -1
        coefs[k] += a
    return coefs

def poly_bernstein(m):
    polynoms = []
    for p in range(m+1):
        coefs = step1(m-p)
        coefs = [0] * p + coefs
        for i in range(p, len(coefs)):
            coefs[i] *= binomial_coef(p, m)
        polynoms.append(coefs)
    return polynoms

def bezier_poly(points_coords):
    n = len(points_coords)
    polys_bernstein = poly_bernstein(n-1)

    x_poly = [0] * n
    y_poly = [0] * n

    for j in range(n):
        for i in range(n):
            x_poly[j] += points_coords[i][0] * polys_bernstein[i][j]
            y_poly[j] += points_coords[i][1] * polys_bernstein[i][j]

    return x_poly, y_poly


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

def fromScreenToEuclidien(coords_sc, min_x_eu, min_y_eu, max_x_eu, max_y_eu, min_x_sc, min_y_sc, max_x_sc, max_y_sc):
    a = min_x_eu
    b = min_y_eu
    c = max_x_eu
    d = max_y_eu
    f = min_x_sc
    g = min_y_sc
    h = max_x_sc
    j = max_y_sc

    eu_coords = []

    for px, py in coords_sc:
        x = ((px - f) * (c - a)) / (h - f) + a
        y = (-((py - j) * (d-b)) / (j - g)) + b
        eu_coords.append((x, y))

    return eu_coords