from spaceTk import SpaceTk

import mathUtils

class ScreenSpaceTk(SpaceTk):

    def __init__(self, euclidianConfigTk, tk_width_pixel=500, tk_height_pixel=400):
        super().__init__(euclidianConfigTk.getRoot(), tk_width_pixel, tk_height_pixel, lambda: self.onRectExpend())

        self.last_lines_drew_id = []
        self.last_coords_eu = []
        self.last_min_x = -1
        self.last_min_y = -1
        self.last_max_x = -1
        self.last_max_y = -1

        super().getRoot().protocol("WM_DELETE_WINDOW", lambda: self.onClose(euclidianConfigTk))

    def onRectExpend(self):
        if (len(self.last_lines_drew_id) != 0):
            self.delete_old_drew_points()
            coords_sc = self.fromEuclidienToScreen(self.last_coords_eu,
                self.last_min_x, self.last_min_y, self.last_max_x, self.last_max_y,
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

    def onClose(self, euclidianConfigTk):
        euclidianConfigTk.removeAScreenSpaceTk(self)
        super().getRoot().destroy()

    def move_window(self, dx, dy):
        final_dx_dy = super().move_window(dx, dy)
        dx = final_dx_dy[0]
        dy = final_dx_dy[1]
        for last_line_drew_id in self.last_lines_drew_id:
            super().getCanvas().move(last_line_drew_id, dx, dy)

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

    def compute_f(self, function_coefs, x_start=None, x_end=None):
        if (x_start == None):
            x_start=self.last_min_x
        if (x_end == None):
            x_end = self.last_max_x

        pas_x = (self.last_max_x - self.last_min_x) / self.getRoot().winfo_width()
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
        Dessine une fonction f tel que:
            - x E [min_x;max_x]
            - y E [min_y;max_y]
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
        self.last_coords_eu.clear()

        # Compute f(x)
        coords_eu = self.compute_f(function_coefs, x_start, x_end)

        self.last_coords_eu.extend(coords_eu)

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

    def draw_segement(self, pointA, pointB, min_x, min_y, max_x, max_y):

        # calcul f(x) = ax + y
        a = (pointB[1] - pointA[1]) / (pointB[0] - pointA[0])
        b = pointA[1] - a * pointA[0]

        self.draw_function(min_x, min_y, max_x, max_y, [a, b], pointA[0], pointB[0])
