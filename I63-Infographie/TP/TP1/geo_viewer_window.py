from window import Window
import window_utils

from segementsViewer import SegementsViewer
from polynomsViewer import PolynomsViewer
from bezier_viewer import BezierViewer

import mathUtils

class GeoViewerWindow(Window):

    def __init__(self, window_id, canvas, x1, y1, x2, y2):
        super().__init__(window_id, canvas, x1, y1, x2, y2)

        self.segements = SegementsViewer(self)
        self.polynom = PolynomsViewer(self)
        self.bezier = BezierViewer(self)

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

        self.points_control_bezier_sc = []
        # Liste des identifiants des carrés (pixels) représentant les points de controle
        # pour la courbe de Bezier  
        self.points_bezier_id = []

    def clear_figures(self):
        """
        Supprime tous les points sur l'écran virtuel
        """
        self.segements.clear_figures()
        self.polynom.clear_figures()
        self.bezier.clear_figures()

    def on_window_expend(self, dpx, dpy):
        """
        Evenement déclanché lorsque l'utilisateur étent la fenêtre virtuelle.
        Met à jour les points de la courbe si la fenêtre est étendue.
        """
        self.segements.on_extend_sc(dpx, dpy)
        self.polynom.on_extend_sc(dpx, dpy)
        self.bezier.on_extend_sc(dpx, dpy)

    def expend_window_left_line(self, current_widget, dx):
        """
        Evenement déclanché lorsque l'utilisateur étend la fenêtre vers la
        gauche.
        """
        super().expend_window_left_line(current_widget, dx)
        self.on_window_expend(dx, 0)

    def expend_window_top_line(self, current_widget, dy):
        """
        Evenement déclanché lorsque l'utilisateur étend la fenetre vers la
        droite.
        """
        super().expend_window_top_line(current_widget, dy)
        self.on_window_expend(0, dy)

    """
    def move_bezier_control_point(self, current_widget, dx, dy):
        for pixel_drew_id in self.last_pixel_drew_id:
            super().getCanvas().delete(pixel_drew_id)
        super().getCanvas().move(current_widget, dx, dy)
        self.redraw_bezier_curve()
    """

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

        self.segements.on_dim_eu_changed()
        self.polynom.on_dim_eu_changed()
        self.bezier.on_dim_eu_changed()

    def get_min_x_eu(self):
        return self.last_min_x
    
    def get_min_y_eu(self):
        return self.last_min_y
    
    def get_max_x_eu(self):
        return self.last_max_x
    
    def get_max_y_eu(self):
        return self.last_max_y
    
    def get_segements_viewer(self):
        return self.segements
    
    def get_polynom_viewer(self):
        return self.polynom
    
    def get_bezier_viewer(self):
        return self.bezier

    def is_out_of_bounds_eu(self, x, y):
        """
        Renvoie True si le point est en dehors de la fenêtre
        """
        return x < self.get_min_x_eu() or x >= self.get_max_x_eu() or y < self.get_min_y_eu() or y >= self.get_max_y_eu()
        

    def from_eu_to_sc(self, points):
        window_extremities = self.get_rect_extremities()
        return mathUtils.fromEuclidienToScreen(points,
            self.get_min_x_eu(), self.get_min_y_eu(), 
            self.get_max_x_eu(), self.get_max_y_eu(),
            window_extremities[0][0],
            window_extremities[0][1],
            window_extremities[1][0],
            window_extremities[1][1]
        )

    def from_sc_to_eu(self, points):
        window_extremities = self.get_rect_extremities()
        return mathUtils.fromScreenToEuclidien(points,
            self.get_min_x_eu(), self.get_min_y_eu(), 
            self.get_max_x_eu(), self.get_max_y_eu(),
            window_extremities[0][0],
            window_extremities[0][1],
            window_extremities[1][0],
            window_extremities[1][1]
        )
        