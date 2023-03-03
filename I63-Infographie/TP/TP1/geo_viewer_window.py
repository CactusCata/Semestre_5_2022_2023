from window import Window
import window_utils

import mathUtils

class GeoViewerWindow(Window):

    def __init__(self, window_id, canvas, x1, y1, x2, y2):
        super().__init__(window_id, canvas, x1, y1, x2, y2)

        # Ensemble contenant les id des pixels dessinés
        # à l'écran
        self.last_pixel_drew_id = []

        # Ensemble des coordonnées de l'espace euclidien
        self.last_coords_eu = []

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
        if (len(self.last_pixel_drew_id) != 0):
            self.delete_old_drew_points()
            self.last_coords_eu.clear()

    def on_window_expend(self):
        """
        Permet de mettre à jour les points de la courbe si la fenêtre
        est étendue.

        - Supprime tous les anciens points
        - Calcul
        """
        if (len(self.last_pixel_drew_id) != 0):
            self.delete_old_drew_points()

            window_extremities = super().get_rect_extremities()
            coords_screen = mathUtils.fromEuclidienToScreen(self.last_coords_eu,
                self.last_min_x, self.last_min_y, self.last_max_x, self.last_max_y,
                window_extremities[0][0],
                window_extremities[0][1],
                window_extremities[1][0],
                window_extremities[1][1]
                )

            for coord in coords_screen:
                pixel_id = super().draw_pixel(coord[0], coord[1])
                self.last_pixel_drew_id.append(pixel_id)

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
        Supprime tous les points de l'espace écran déssinés
        """
        for pixel_drew_id in self.last_pixel_drew_id:
            super().getCanvas().delete(pixel_drew_id)
        self.last_pixel_drew_id.clear()

    def compute_f(self, function_coefs, x_start, x_end):
        """
        Calcul l'ensemble E = {f(x) | x E [x_start;x_end]}
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

    def draw_function(self, min_x, min_y, max_x, max_y, function_coefs, x_start=None, x_end=None):
        """
        Dessine une fonction polynomiale f:
            min_x: correspond au x à gauche de la fenêtre
            min_y: correspond au y en bas de la fenêtre
            max_x: correspond au x à droite de la fenêtre
            max_y: correspond au y en haut de la fenêtre
            function_coefs: liste des coefficients du polynome
            (x_start, x_end): permet de dessiner un portion de la courbe (de x_start à x_end)
        """

        if (x_start == None):
            x_start = min_x
        if (x_end == None):
            x_end = max_x


        self.last_min_x = min_x
        self.last_min_y = min_y
        self.last_max_x = max_x
        self.last_max_y = max_y

        # Delete old points
        self.delete_old_drew_points()

        # Compute f(x)
        self.last_coords_eu.extend(self.compute_f(function_coefs, x_start, x_end))

        # from euclidian space to screen space
        window_extremities = super().get_rect_extremities()
        coords_screen = mathUtils.fromEuclidienToScreen(self.last_coords_eu,
            min_x, min_y, max_x, max_y,
            window_extremities[0][0],
            window_extremities[0][1],
            window_extremities[1][0],
            window_extremities[1][1]
            )

        # Draw f(x) in screen space
        for coord in coords_screen:
            pixel_id = super().draw_pixel(coord[0], coord[1])
            self.last_pixel_drew_id.append(pixel_id)

    def draw_segement_Bresenham(self, xa, ya, xb, yb):
        """
        Renvoie un ensemble de coordonnées pour l'espace écran
        """
        pixels_coord = []

        if (xb < xa): # Quartier 3,4,5,6
            if (yb < ya): # Quartier 5,6
                if (-yb < -xb): # Quartier 5
                    return
                else: # Quartier 6
                    return
            else: # Quartier 3,4
                if (yb < -xb): # Quartier 4
                    return
                else: # Quartier 3
                    return
        else: # Quartier 1,2,7,8
            if (yb < ya): # Quartier 7,8
                if (-yb < xb): # Quartier 8
                    return
                else: # Quartier 7
                    return
            else: # Quartier 1,2
                if (yb < xb): # Quartier 1
                    dx = xb - xa
                    dy = yb - ya
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
                    return





        return pixels_coord

    def draw_segement(self, pointA, pointB, min_x, min_y, max_x, max_y):
        window_extremities = super().get_rect_extremities()
        coords_AB = mathUtils.fromEuclidienToScreen([pointA, pointB],
            min_x, min_y, max_x, max_y,
            window_extremities[0][0],
            window_extremities[0][1],
            window_extremities[1][0],
            window_extremities[1][1]
        )
        pixels_coord = self.draw_segement_Bresenham(
            coords_AB[0][0], coords_AB[0][1],
            coords_AB[1][0], coords_AB[1][1]
        )
        print("wtf")
        for coord in pixels_coord:
            pixel_id = super().draw_pixel(coord[0], coord[1])
            self.last_pixel_drew_id.append(pixel_id)


    def draw_segement_old(self, pointA, pointB, min_x, min_y, max_x, max_y):

        # calcul f(x) = ax + y
        a = (pointB[1] - pointA[1]) / (pointB[0] - pointA[0])
        b = pointA[1] - a * pointA[0]

        self.draw_function(min_x, min_y, max_x, max_y, [a, b], pointA[0], pointB[0])
