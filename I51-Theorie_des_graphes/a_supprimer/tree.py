class Tree:

    def __init__(self, data, sonAmount):
        self.data = date
        self.sons = [None] * sonAmount

    def getData(self):
        return self.data

    def setSon(self, index, tree):
        self.sons[index] = tree

    def getSon(self, index):
        return self.sons[index]
