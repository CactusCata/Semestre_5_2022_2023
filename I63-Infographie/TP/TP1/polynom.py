import mathUtils

class Polynom():

    def __init__(self, coefs):
        self.coefs = coefs
        self.__len__ = len(coefs)

        self.f_values_eu = []

    def compute_f(self, min_x, min_y, max_x, max_y, start_x=None, end_x=None, stepAmount=20):
        """
        stepAmount correspond au nombre de valeur
        de x tq:
            E = {f(x) | x E [x_start;x_end]}
        """

        start_x = min_x if start_x == None else start_x
        end_x = max_x if end_x == None else end_x

        pas_x = (end_x - start_x) / stepAmount
        self.f_values_eu = []
        x = start_x
        while x <= end_x:
            y = mathUtils.horner(x, self.coefs)
            if (min_y < y < max_y):
                self.f_values_eu.append([x, y])
            x += pas_x

    def get_f_values(self):
        return self.f_values_eu
    
    def copy(self):
        return Polynom(self.coefs.copy())
    
    def __iadd__(self, polynom):
        biggestPoly = polynom
        minusPoly = self
        if (len(biggestPoly) < len(self)):
            biggestPoly = self
            minusPoly = biggestPoly

        for i in range(len(minusPoly)):
            biggestPoly.coefs[i] += minusPoly.coefs[i]

        return self

        
