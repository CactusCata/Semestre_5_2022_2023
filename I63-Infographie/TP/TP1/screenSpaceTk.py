from spaceTk import SpaceTk

import mathUtils

class ScreenSpaceTk(SpaceTk):

    def __init__(self, master, tk_width_pixel=500, tk_height_pixel=400):
        super().__init__(master, tk_width_pixel, tk_height_pixel)

        self.last_lines_drew_id = []

    def fromEuclidienToScreen(self, coords_list, min_x_eu, min_y_eu, max_x_eu, max_y_eu, min_x_sc, min_y_sc, max_x_sc, max_y_sc):
        a = min_x_eu
        b = min_y_eu
        c = max_x_eu
        d = max_y_eu
        f = min_x_sc
        g = min_y_sc
        h = max_x_sc
        j = max_y_sc

        m = super().getRoot().winfo_height()

        screen_coords = []

        for x, y in coords_list:
            px = int(((x - a) * (h - f)) / (c - a) + f)
            py = int(-(((j - g) * (y - b)) / (d - b)) + j)
            screen_coords.append((px, py))

        return screen_coords

    def delete_old_drew_points(self):
        """
        Supprime tous les points de l'espace écran déssinés
        """
        for last_line_drew_id in self.last_lines_drew_id:
            super().getCanvas().delete(last_line_drew_id)
        self.last_lines_drew_id.clear()

    def draw_function(self, min_x, min_y, max_x, max_y, function_coefs):
        """
        Dessine une fonction f tel que:
            - x E [min_x;max_x]
            - y E [min_y;max_y]
        """

        # Delete old points
        self.delete_old_drew_points()

        # Compute f(x)
        pas_x = (max_x - min_x) / self.getRoot().winfo_width()
        x = min_x
        coords_eu = []
        while x <= max_x:
            y = mathUtils.horner(x, function_coefs)
            if min_y < y < max_y:
                coords_eu.append((x, y))
            x += pas_x

        # from euclidian space to screen space
        coords_sc = self.fromEuclidienToScreen(coords_eu,
            min_x, min_y, max_x, max_y,
            super().getTopLeftRect()[0],
            super().getTopLeftRect()[1],
            super().getBotRightRect()[0],
            super().getBotRightRect()[1]
            )

        # Draw f(x) in screen space
        first_point = coords_sc[0]
        for coord in coords_sc:
            line_id = super().getCanvas().create_line(first_point[0], first_point[1], coord[0], coord[1])
            first_point = coord
            self.last_lines_drew_id.append(line_id)