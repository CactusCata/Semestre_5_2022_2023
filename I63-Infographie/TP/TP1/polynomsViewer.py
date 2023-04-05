from segementsViewer import SegementsViewer
from polynom import Polynom

class PolynomsViewer():

    def __init__(self, geo_viewer):
        self.geo_viewer = geo_viewer

        self.polynoms = {}

    def clear_figures(self):
        self.polynom = None
        for segementsViewer in self.polynoms.values():
            segementsViewer.clear_figures()

    def clear_pixels(self):
        for segementsViewer in self.polynoms.values():
            segementsViewer.clear_pixels()

    def add_polynoms_eu(self, all_coefs_eu, x_start=None, x_end=None):
        for function_coefs_eu in all_coefs_eu:
            polynom = Polynom(function_coefs_eu)
            polynom.compute_f(
                self.geo_viewer.get_min_x_eu(), self.geo_viewer.get_min_y_eu(), 
                self.geo_viewer.get_max_x_eu(), self.geo_viewer.get_max_y_eu(),
                x_start, x_end)

            # Add segements
            f_values_eu = polynom.get_f_values()
            back_point = f_values_eu[0]
            segements_array = []
            for i in range(1, len(f_values_eu)):
                segements_array.append(back_point)
                segements_array.append(f_values_eu[i])
                back_point = f_values_eu[i]

            segementsViewer = SegementsViewer(self.geo_viewer)
            segementsViewer.add_segements_eu(segements_array)
            self.polynoms[polynom] = segementsViewer

    def draw(self):
        for segementsViewer in self.polynoms.values():
            segementsViewer.draw()

    def redraw(self):
        for segementsViewer in self.polynoms.values():
            segementsViewer.redraw()

    def on_move(self, dpx, dpy):
        for segementsViewer in self.polynoms.values():
            segementsViewer.on_move(dpx, dpy)

    def on_extend_sc(self, dpx, dpy):
        for segementsViewer in self.polynoms.values():
            segementsViewer.on_extend_sc(dpx, dpy)
    
    def on_dim_eu_changed(self):
        for polynom in self.polynoms.keys():
            polynom.compute_f(
                self.geo_viewer.get_min_x_eu(), self.geo_viewer.get_min_y_eu(), 
                self.geo_viewer.get_max_x_eu(), self.geo_viewer.get_max_y_eu())

