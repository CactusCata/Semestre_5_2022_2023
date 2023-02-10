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
