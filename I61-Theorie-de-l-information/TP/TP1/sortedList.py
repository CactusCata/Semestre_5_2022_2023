class SortedList():

    def __init__(self, keyIndex=0) -> None:
        self.array = []
        self.keyIndex = keyIndex

    def append(self, element: tuple) -> None:
        a = 0
        b = len(self.array) - 1
        middle = (b + a) // 2

        while (a <= b):
            if element[self.keyIndex] < self.array[middle][self.keyIndex]:
                b = middle - 1
            elif element[self.keyIndex] > self.array[middle][self.keyIndex]:
                a = middle + 1
            else:
                self.array.insert(middle, element)
                return
            middle = (b + a) >> 1

        self.array.insert(a, element)

