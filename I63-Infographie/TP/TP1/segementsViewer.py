import mathUtils
import window_utils

class SegementsViewer():

    def __init__(self, geo_viewer):
        self.geo_viewer = geo_viewer

        # Liste des coordonnées des segements
        # qui seront déssinés à l'écran 
        self.segements_eu = []
        self.segements_unsafe_eu = []

        # Liste des identifiants tkinter des points
        # représentants les pixels du segement 
        self.pixels_drew_id = []

    def clear_figures(self):
        """
        Permet de supprimer tous les segements
        """
        self.clear_pixels()
        self.segements_eu.clear()

    def clear_pixels(self):
        """
        Permet de supprimer tous les pixels déssinés
        """
        for pixel_drew_id in self.pixels_drew_id:
            self.geo_viewer.getCanvas().delete(pixel_drew_id)
        self.pixels_drew_id.clear()

    def add_segements_eu(self, segements_eu):
        """
        Enregistre de nouveaux segements (coordonnées euclidiennes) dans 
        la liste des segements à dessiner

        segements_eu: [(2,5),(7,9),(7,6),(2,3)] définis deux
            segements:
                - (2,5) à (7,9)
                - (7,6) à (2,3)
        """
        self.segements_eu.extend(segements_eu)

    def add_unsafe_segement_eu(self, pointA, pointB):
        """
        Enregistre de nouveaux segements qui pourraient être
        en dehors de la fenetre
        """
        window_extremities = self.geo_viewer.get_rect_extremities()
        segements_sc = self.geo_viewer.from_eu_to_sc([pointA, pointB])

        pixels_coord = window_utils.draw_segement_sc_Bresenham(
            segements_sc[0][0], segements_sc[0][1],
            segements_sc[1][0], segements_sc[1][1]
        )

        indexs = window_utils.get_safe_segement_extremities_index(pixels_coord, window_extremities)

        if (indexs != None):
            safe_segement_eu = self.geo_viewer.from_sc_to_eu([pixels_coord[indexs[0]], pixels_coord[indexs[1]]])
            print(safe_segement_eu)
            self.add_segements_eu([safe_segement_eu[0], safe_segement_eu[1]])


    def draw(self):
        """
        Affiche les pixels sur l'écran virtuel
        """
        segements_sc = self.geo_viewer.from_eu_to_sc(self.segements_eu)

        for i in range(0, len(segements_sc), 2):
            pointA = segements_sc[i]
            pointB = segements_sc[i+1]
            pixels_coord = window_utils.draw_segement_sc_Bresenham(
                pointA[0], pointA[1],
                pointB[0], pointB[1]
            )
            for coord in pixels_coord:
                pixel_id = self.geo_viewer.draw_pixel(coord[0], coord[1])
                self.pixels_drew_id.append(pixel_id)

    def draw_unsafe(self):
        segements_sc = self.geo_viewer.from_eu_to_sc(self.segements_unsafe_eu)

        for i in range(0, len(segements_sc), 2):
            pointA = segements_sc[i]
            pointB = segements_sc[i+1]
            pixels_coord = window_utils.draw_segement_sc_Bresenham(
                pointA[0], pointA[1],
                pointB[0], pointB[1]
            )

            for coord in pixels_coord:
                pixel_id = self.geo_viewer.draw_pixel(coord[0], coord[1])
                self.pixels_drew_id.append(pixel_id)

    def redraw(self):
        """
        Affiche les pixels sur l'écran virtuel
        """
        self.draw()

    def draw_old(self, pointA, pointB, min_x, min_y, max_x, max_y):
        """
        Ancienne méthode (moins optimisée) permetant de dessiner des segements
        """

        # calcul f(x) = ax + y
        a = (pointB[1] - pointA[1]) / (pointB[0] - pointA[0])
        b = pointA[1] - a * pointA[0]

        self.draw_function(min_x, min_y, max_x, max_y, [a, b], pointA[0], pointB[0])

    def on_move(self, dpx, dpy):
        """
        Fonction appelée lorsque l'utilisateur déplace la fenetre virtuelle
        """
        # On déplace bien tous les points
        for pixel_drew_id in self.pixels_drew_id:
            self.geo_viewer.getCanvas().move(pixel_drew_id, dpx, dpy)

    def on_extend_sc(self, dpx, dpy):
        """
        Fonction appelée lorsque l'utilisateur étend la fenetre
        """
        self.clear_pixels()
        self.redraw()

    def on_dim_eu_changed(self):
        self.clear_pixels()
        self.redraw()