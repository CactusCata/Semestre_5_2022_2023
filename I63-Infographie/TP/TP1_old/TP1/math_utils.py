from space_partition import SpacePartition

def horner(x: float, coefs: list) -> int:
    """
    Evalue la fonction polynomiale en x
    """
    sum = coefs[-1]
    for coef_index in range(len(coefs) - 2, -1, -1):
            sum *= x
            sum += coefs[coef_index]
    return sum

def euclidean_space_to_screen_space(px: int, py: int, screenHeight:int, window: SpacePartition, viewport: SpacePartition):
    """
    Projecte un point de l'espace euclidien
    dans l'espace view
    """
    a = window.get_x1()
    b = window.get_y1()
    c = window.get_x2()
    d = window.get_y2()
    f = viewport.get_x1()
    g = viewport.get_y1()
    h = viewport.get_x2()
    j = viewport.get_y2()
    m = screenHeight

    xTransformed = f + ((-f + h)*(-a + px))/(-a + c)
    yTransformed = -h + m - ((-g + j)*(-b + py))/(-b + d)

    return (xTransformed, yTransformed)
