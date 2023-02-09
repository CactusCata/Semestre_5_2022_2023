from tkinter import Tk, Canvas
import os
from space_partition import SpacePartition
from space import Space, INDIRECT, DIRECT
import file_utils
import math_utils

def generate_window(tk_canvas: Canvas, x1: int, y1: int, x2: int, y2: int) -> SpacePartition:
    """
    Dessine une fenêtre à l'écran et l'enregistre dans la liste des windows
    Renvoie une instance de la SpacePartition
    """
    window = SpacePartition(x1, y1, x2, y2)
    window.draw(tk_canvas)
    return window

def generate_function(window: SpacePartition, x_min: int, x_max: int, nb_point: int, *coefs) -> list:
    if (x_min < window.get_x1()):
        x_min = window.get_x1()

    if (x_max > window.get_x2()):
        x_max = window.get_x2()

    step = (x_max - x_min + 1) / nb_point
    function_points = []
    while nb_point != 0:
        evalved_function = horner(x_min, coefs)
        function_points.append((x_min, evalved_function))
        print(evalved_function)

        x_min += step
        nb_point -= 1

    return function_points

def project_points_from_euclidean_space_to_screen_space(points: list, window: SpacePartition, viewport: SpacePartition) -> list:
    projected_points = []

    for point in points:
        projected_points.append(math_utils.euclidean_space_to_screen_space(point[0], point[1], window, viewport))

    return projected_points

def onB1ClickEvent(event):
    """
    Fonction déclanchée lorsque l'utilisateur
    clic dans le canvas avec B1 (clic gauche)
    """
    print(f"Clic at ({event.x},{event.y})")

if __name__ == "__main__":
    tk_root = Tk()
    tk_root_dimensions = (400, 400)
    tk_root.geometry(f"{tk_root_dimensions[0]}x{tk_root_dimensions[1]}")

    tk_canvas = Canvas(tk_root)
    tk_canvas.pack()

    tk_canvas.bind("<Button-1>", onB1ClickEvent)




    # position du point à dessiner par rapport au repère indirect E1
    point_tk_indirect = (130, 90)

    # position pour le repere tkinter direct
    point_tk_direct = (point_tk_indirect[0], tk_root_dimensions[1] - point_tk_indirect[1])

    # position repère E2 par rapport au repère E1 indirect
    point_repere_E2_on_E1 = (110, 150)

    # passage au repère 2
    point_tk_E2 = (point_tk_direct[0] - )
    # go E1 indirect to E2 direct
    point = ()


    """


    # Espace de la fenêtre tkinter
    space_tk = Space(INDIRECT)

    sub_space_window = Space(DIRECT)
    sub_space_window.add_window(20, 30) # beta position relative par rapport à son espace

    space_tk.add_subspace(50, 150, sub_space_window) # alpha position en pixel dans le repère indirect

    sub_space_viewport = Space(INDIRECT)
    sub_space_window.add_window() #

    space_tk.add_subspace(200, 70, sub_space_viewport) # phi
    """


    # Simule une window
    window_eulerian = generate_window(tk_canvas, 20, 20, 100, 100)

    # Simule une viewspace
    view_space = generate_window(tk_canvas, 150, 150, 250, 250)

    # Deplace la window
    #move_window(tk_canvas, window_eulerian, 100, 100)

    pointWindow = (50, 50)
    pointView = math_utils.euclidean_space_to_screen_space(
        pointWindow[0], pointWindow[1],
        tk_root_dimensions[1],
        window_eulerian,
        view_space)

    window_eulerian.draw_points(tk_canvas, [pointWindow])
    view_space.draw_points(tk_canvas, [pointView])

    tk_root.mainloop()
