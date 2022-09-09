class DotInfo:

    def __init__(self):
        self.graphRelations = []

    def appendPair(self, e1, e2):
        self.graphRelations.append((e1, e2))

    def getGraphRelations(self):
        return self.graphRelations
