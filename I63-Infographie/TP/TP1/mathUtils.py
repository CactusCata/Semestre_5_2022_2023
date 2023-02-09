def horner(x, coefs) -> float:
    """
    coefs = [a, b, c, d, e]
    Eval the polynom P(x) = ax^4 + bx^3 + cx^2 + dx + e
    """
    sum = coefs[0]
    for coef in coefs[1:]:
        sum *= x
        sum += coef
    return sum