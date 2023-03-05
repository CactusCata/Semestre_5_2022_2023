from window import Window
import window_utils

import mathUtils

class GeoViewerWindow(Window):

    def __init__(self, window_id, canvas, x1, y1, x2, y2):
        super().__init__(window_id, canvas, x1, y1, x2, y2)

        # Ensemble contenant les id des pixels dessinés
        # à l'écran
        self.last_pixel_drew_id = []

        # Ensemble des coordonnées de l'espace euclidien pour les polynomes
        self.last_coords_poly_eu = []
        # Ensemble contenant les positions des points extrémités des segements
        # de l'espace euclidien
        self.last_coords_segements_eu = []

        # Echelle mathématique pour qu'on ai:
        #
        #               (max_x, max_y)
        #       +--------+
        #       |        |
        #       +--------+
        #  (min_x, min_y)
        #
        self.last_min_x = -1
        self.last_min_y = -1
        self.last_max_x = -1
        self.last_max_y = -1

    def clear_figures(self):
        """
        Supprime tous les points sur l'écran virtuel
        """
        if (len(self.last_pixel_drew_id) != 0):
            self.delete_old_drew_points()
            self.last_coords_poly_eu.clear()
            self.last_coords_segements_eu.clear()

    def on_window_expend(self):
        """
        Evenement déclanché lorsque l'utilisateur étent la fenêtre virtuelle.
        Met à jour les points de la courbe si la fenêtre est étendue.
        """
        if (len(self.last_pixel_drew_id) != 0):
            self.delete_old_drew_points()
            self.redraw_polynoms()
            self.redraw_segements()

    def expend_window_left_line(self, current_widget, dx):
        """
        Evenement déclanché lorsque l'utilisateur étend la fenêtre vers la
        gauche.
        """
        super().expend_window_left_line(current_widget, dx)
        self.on_window_expend()

    def expend_window_top_line(self, current_widget, dy):
        """
        Evenement déclanché lorsque l'utilisateur étend la fenetre vers la
        droite.
        """
        super().expend_window_top_line(current_widget, dy)
        self.on_window_expend()

    def move_window(self, dx, dy):
        """
        Evenement déclanché lorsque l'utilisateur déplace le fenêtre.
        """
        final_dx_dy = super().move_window(dx, dy)
        dx = final_dx_dy[0]
        dy = final_dx_dy[1]
        for last_line_drew_id in self.last_pixel_drew_id:
            super().getCanvas().move(last_line_drew_id, dx, dy)

    def delete_old_drew_points(self):
        """
        Supprime tous les points de l'espace écran déssinés précédemment
        """
        for pixel_drew_id in self.last_pixel_drew_id:
            super().getCanvas().delete(pixel_drew_id)
        self.last_pixel_drew_id.clear()

    def euclidian_space_dim_changed(self, min_x: int, min_y: int, max_x: int, max_y: int):
        """
        min_x: correspond au x à gauche de la fenêtre
        min_y: correspond au y en bas de la fenêtre
        max_x: correspond au x à droite de la fenêtre
        max_y: correspond au y en haut de la fenêtre
        """
        self.last_min_x = min_x
        self.last_min_y = min_y
        self.last_max_x = max_x
        self.last_max_y = max_y

        if (len(self.last_pixel_drew_id) != 0):
            self.delete_old_drew_points()
            self.redraw_polynoms()
            self.redraw_segements()

    def compute_f(self, function_coefs, x_start, x_end):
        """
        Calcul l'ensemble E = {f(x) | x E [x_start;x_end]} d'une fonction polynomiale
        """

        pas_x = (self.last_max_x - self.last_min_x) / window_utils.CURRENT_ROOT_WIDTH
        x = x_start
        coords_eu = []
        while x <= x_end:
            y = mathUtils.horner(x, function_coefs)
            if self.last_min_y < y < self.last_max_y:
                coords_eu.append((x, y))
            x += pas_x
        return coords_eu
    
    def redraw_polynoms(self):
        """
        Dessine les points des polynomes
        """
        self.draw_polynom(self.last_coords_poly_eu)

    def draw_polynom(self, polynom_points):
        """
        Dessine les point d'un polynome en particulier
        """

        # from euclidian space to screen space
        window_extremities = super().get_rect_extremities()
        coords_screen = mathUtils.fromEuclidienToScreen(polynom_points,
            self.last_min_x, self.last_min_y, self.last_max_x, self.last_max_y,
            window_extremities[0][0],
            window_extremities[0][1],
            window_extremities[1][0],
            window_extremities[1][1]
            )

        # Draw f(x) in screen space
        for coord in coords_screen:
            pixel_id = super().draw_pixel(coord[0], coord[1])
            self.last_pixel_drew_id.append(pixel_id)

    def add_polynom(self, function_coefs, x_start=None, x_end=None):
        """
        Dessine une fonction polynomiale f:

            function_coefs: liste des coefficients du polynome
            (x_start, x_end): permet de dessiner un portion de la courbe (de x_start à x_end)
        """

        if (x_start == None):
            x_start = self.last_min_x
        if (x_end == None):
            x_end = self.last_max_x


        # Delete old points
        #self.delete_old_drew_points()

        polynom_points = self.compute_f(function_coefs, x_start, x_end)

        # Compute f(x)
        self.last_coords_poly_eu.extend(polynom_points)

        self.draw_polynom(polynom_points)

    def draw_segement_Bresenham(self, xa, ya, xb, yb):
        """
        Renvoie un ensemble de coordonnées pour l'espace écran
        """
        print(f"{(xa,ya)} à {(xb,yb)}")
        pixels_coord = []
        dx = xb - xa
        dy = yb - ya

        if (xb < xa): # Quartier 3,4,5,6
            if (yb < ya): # Quartier 5,6
                if (-dy < -dx): # Quartier 5
                    print("Quartier 5")
                    dec = -dx - 2 * -dy
                    x = xa
                    y = ya
                    while (x >= xb):
                        pixels_coord.append((x, y))
                        if dec < 0:
                            dec += 2 * -dx
                            y -= 1
                        dec -= 2 * -dy
                        x -= 1
                else: # Quartier 6
                    print("Quartier 6")
                    dec = -dy + 2 * dx
                    x = xa
                    y = ya
                    while (y >= yb):
                        pixels_coord.append((x, y))
                        if dec < 0:
                            dec += 2 * -dy
                            x -= 1
                        dec += 2 * dx
                        
                        y -= 1
            else: # Quartier 3,4
                if (dy < -dx): # Quartier 4
                    print("Quartier 4")
                    dec = -dx - 2 * dy
                    x = xa
                    y = ya
                    while (x >= xb):
                        pixels_coord.append((x, y))
                        if dec < 0:
                            dec += 2 * -dx
                            y += 1
                        dec -= 2 * dy
                        x -= 1
                else: # Quartier 3
                    print("Quartier 3")
                    dec = dy + 2 * dx
                    x = xa
                    y = ya
                    while (y <= yb):
                        pixels_coord.append((x, y))
                        if dec < 0:
                            dec += 2 * dy
                            x -= 1
                        dec -= 2 * -dx
                        y += 1

        else: # Quartier 1,2,7,8
            if (yb < ya): # Quartier 7,8
                if (-dy < dx): # Quartier 8
                    print("Quartier 8")
                    dec = dx + 2 * dy
                    x = xa
                    y = ya
                    while (x <= xb):
                        pixels_coord.append((x, y))
                        if dec < 0:
                            dec += 2 * dx
                            y -= 1
                        dec += 2 * dy
                        x += 1
                else: # Quartier 7
                    print("Quartier 7")
                    dec = -dy + 2 * dx
                    x = xa
                    y = ya
                    while (y >= yb):
                        pixels_coord.append((x, y))
                        if dec < 0:
                            dec -= 2 * dy
                            x += 1
                        dec -= 2 * dx
                        y -= 1

            else: # Quartier 1,2
                if (dy < dx): # Quartier 1
                    print("Quartier 1")
                    dec = dx - 2 * dy
                    x = xa
                    y = ya
                    while (x <= xb):
                        pixels_coord.append((x, y))
                        if dec < 0:
                            dec += 2 * dx
                            y += 1
                        dec -= 2 * dy
                        x += 1
                else: # Quartier 2
                    print("Quartier 2")
                    dec = dy - 2 * dx
                    x = xa
                    y = ya
                    while (y <= yb):
                        pixels_coord.append((x, y))
                        if dec < 0:
                            dec += 2 * dy
                            x += 1
                        dec -= 2 * dx
                        y += 1

        print(f"res = {pixels_coord}")
        return pixels_coord

    def redraw_segements(self):
        """
        Redessine tous les segements
        """
        print(f"Points extremities des segements: {self.last_coords_segements_eu}")
        for i in range(0, len(self.last_coords_segements_eu), 2):
            pointA = self.last_coords_segements_eu[i]
            pointB = self.last_coords_segements_eu[i+1]
            self.draw_segement(pointA, pointB)

    def draw_segement(self, pointA, pointB):
        """
        Dessine un unique segement allant du point A au point B
        """
        window_extremities = super().get_rect_extremities()
        coords_AB_sc = mathUtils.fromEuclidienToScreen([pointA, pointB],
            self.last_min_x, self.last_min_y, self.last_max_x, self.last_max_y,
            window_extremities[0][0],
            window_extremities[0][1],
            window_extremities[1][0],
            window_extremities[1][1]
        )
        pixels_coord = self.draw_segement_Bresenham(
            coords_AB_sc[0][0], coords_AB_sc[0][1],
            coords_AB_sc[1][0], coords_AB_sc[1][1]
        )
        for coord in pixels_coord:
            pixel_id = super().draw_pixel(coord[0], coord[1])
            self.last_pixel_drew_id.append(pixel_id)


    def add_segement(self, pointA: tuple[int, int], pointB: tuple[int, int]):
        """
        Dessine un nouveau segement sur la fenêtre virtuelle

        :pointA: (xa, ya)
        :pointB: (xb, yb)
        """
        self.last_coords_segements_eu.extend([pointA, pointB])
        self.draw_segement(pointA, pointB)

    def draw_segement_old(self, pointA, pointB, min_x, min_y, max_x, max_y):

        # calcul f(x) = ax + y
        a = (pointB[1] - pointA[1]) / (pointB[0] - pointA[0])
        b = pointA[1] - a * pointA[0]

        self.draw_function(min_x, min_y, max_x, max_y, [a, b], pointA[0], pointB[0])
