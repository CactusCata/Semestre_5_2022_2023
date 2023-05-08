from math import sqrt, cos, sin
from tkinter import Tk, Canvas

def produit_scalaire(vec2D_A:tuple, vec2D_B:tuple):
    return vec2D_A[0] * vec2D_B[0] + vec2D_A[1] * vec2D_B[1]

def is_convexe(p1:tuple, p2:tuple, p3:tuple):
    # Translate points (become vector)
    p1 = (p1[0] - p2[0], p1[1] - p2[1])
    p3 = (p3[0] - p2[0], p3[1] - p2[1])

    # Apply rotation of p1 of 270 degre
    p1 = (p1[1], -p1[0])

    return produit_scalaire(p1, p3) > 0

def poly_is_convexe(poly):
    n = len(poly)
    for i in range(n):
        p1 = poly[i % n]
        p2 = poly[(i + 1) % n]
        p3 = poly[(i + 2) % n]
        if (not is_convexe(p1, p2, p3)):
            return False
    return True

def draw_poly(canvas: Canvas, poly):
    expend_value = 10
    shift_value = 30
    n = len(poly)
    for i in range(n):
        canvas.create_line(poly[i][0] * expend_value + shift_value,
                            poly[i][1] * expend_value + shift_value, 
                            poly[(i + 1) % n][0] * expend_value + shift_value,
                            poly[(i + 1) % n][1] * expend_value + shift_value)

if __name__ == "__main__":
    root = Tk()
    canvas = Canvas(root)
    canvas.pack()
    p1 = [
        (0, 0),
        (6, 0),
        (3, 6)
    ]

    print(poly_is_convexe(p1))
                          
    p2 = [
        (0, 0),
        (2, 0),
        (2, 2),
        (0, 2)
    ]

    print(poly_is_convexe(p2))
    
    p3 = [
        (0, 0),
        (3, 3),
        (6, 0),
        (3, 6)
    ]

    print(poly_is_convexe(p3))
    draw_poly(canvas, p3)

    root.mainloop()