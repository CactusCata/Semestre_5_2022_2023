from segementsViewer import SegementsViewer

import mathUtils

class BezierViewer():

    def __init__(self, geo_viewer):
        self.geo_viewer = geo_viewer

        self.segement_viewer = SegementsViewer(self.geo_viewer)

        self.control_points_eu = []
        self.control_points_id = []

        self.polynom_bezier_x_eu = []
        self.polynom_bezier_y_eu = []

        self.geo_viewer.add_command("Ajouter un point de bezier", self.add_bezier_control_point_sc)

    def clear_figures(self):
        self.clear_pixels()
        self.segement_viewer.clear_figures()
        self.polynom_bezier_x_eu.clear()
        self.polynom_bezier_y_eu.clear()

        for control_point_id in self.control_points_id:
            self.geo_viewer.getCanvas().delete(control_point_id)
        self.control_points_id.clear()
        self.control_points_eu.clear()


    def clear_pixels(self):
        self.__clear_pixels_control_points()
        self.segement_viewer.clear_pixels()

    def add_bezier_control_points_eu(self, control_points_eu):
        self.control_points_eu.extend(control_points_eu)
        self.polynom_bezier_x_eu, self.polynom_bezier_y_eu = mathUtils.bezier_poly(self.control_points_eu)

    def add_bezier_control_point_sc(self, px, py):
        control_point_eu = self.geo_viewer.from_sc_to_eu([(px, py)])
        self.add_bezier_control_points_eu(control_point_eu)

        self.clear_pixels()
        self.segement_viewer.clear_figures()
        self.draw_bezier_control_points()
        self.draw()

    def draw_bezier_control_points(self):
        points_control_bezier_sc = self.geo_viewer.from_eu_to_sc(self.control_points_eu)
        for control_point_eu in points_control_bezier_sc:
            control_point_id = self.geo_viewer.draw_pixel(control_point_eu[0], control_point_eu[1], color="blue", size=5)
            self.control_points_id.append(control_point_id)

    def __clear_pixels_control_points(self):
        for control_point_id in self.control_points_id:
            self.geo_viewer.getCanvas().delete(control_point_id)
        self.control_points_id.clear()

    def draw(self):

        self.polynom_bezier_x_eu.reverse()
        self.polynom_bezier_y_eu.reverse()
        sample_amount = 20
        last_x = mathUtils.horner(0, self.polynom_bezier_x_eu)
        last_y = mathUtils.horner(0, self.polynom_bezier_y_eu)
        u = 1 / sample_amount
        while u <= 1 + 1/sample_amount:
            x = mathUtils.horner(u, self.polynom_bezier_x_eu)
            y = mathUtils.horner(u, self.polynom_bezier_y_eu)
            if (self.geo_viewer.is_out_of_bounds_eu(last_x, last_y)):
                if (self.geo_viewer.is_out_of_bounds_eu(x, y)):
                    pass
                else:
                    self.segement_viewer.add_unsafe_segement_eu((last_x, last_y), (x, y))
            else:
                if (self.geo_viewer.is_out_of_bounds_eu(x, y)):
                    self.segement_viewer.add_unsafe_segement_eu((last_x, last_y), (x, y))
                else:
                    self.segement_viewer.add_segements_eu([(last_x, last_y), (x, y)])
            last_x = x
            last_y = y
            u += 1 / sample_amount

        self.segement_viewer.draw()
        
        self.polynom_bezier_x_eu.reverse()
        self.polynom_bezier_y_eu.reverse()

    def redraw(self):
        self.segement_viewer.redraw()

    def on_move(self, dpx, dpy):
        self.segement_viewer.on_move(dpx, dpy)
        for control_point_id in self.control_points_id:
            self.geo_viewer.getCanvas().move(control_point_id, dpx, dpy)

    def on_extend_sc(self, dpx, dpy):
        
        if (len(self.control_points_eu) > 1):
            self.clear_pixels()
            self.redraw()
            self.draw_bezier_control_points()
        else:
            self.segement_viewer.on_extend_sc(dpx, dpy)

    
    def on_dim_eu_changed(self):
        self.segement_viewer.on_dim_eu_changed()
        if (len(self.control_points_eu) > 1):
            self.clear_pixels()
            self.redraw()