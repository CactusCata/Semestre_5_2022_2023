from queue import Queue
from tree import Tree
from time import sleep
from random import randint

def getNeighboursOf(G, point):
    X = G[0]
    U = G[1]
    neighbours = []
    for relatedItem in U:
        if relatedItem[0] == point:
            neighbours.append(relatedItem[1])
        elif relatedItem[1] == point:
            neighbours.append(relatedItem[0])
    return neighbours

def parcourLargeur(G, start, end):
    """
    Fonction non-optimisée
    """
    s = start
    queue = Queue()
    queue.enqueue(s)
    alreadyReachedElements = [s]
    applicationReverse = []

    while queue.getQueueSize() != 0 and s != end:
        s = queue.dequeue()
        for neighbour in getNeighboursOf(G, s):
            if neighbour not in alreadyReachedElements:
                queue.enqueue(neighbour)
                applicationReverse.append((neighbour, s))
                alreadyReachedElements.append(neighbour)

    if s == end:
        path = []
        n = len(applicationReverse)
        while s != start:
            i = 0
            finded = False
            while i < n and not finded:
                antecedant = applicationReverse[i][0]
                image = applicationReverse[i][1]
                if antecedant == s:
                    path.append(image)
                    s = image
                    finded = True
                i += 1
        path.reverse()
        path.append(end)
        return path

    else: # There is not solution
        return None

def parcourLargeurOpti(G, start, end):
    """
    Fonction optimisée
    Elle permet de rechercher dans la partie
    path uniquement les relations de la profondeur
    attendue
    """
    s = start
    queue = Queue()
    queue.enqueue(s)
    alreadyReachedElements = [s]
    applicationReverseDict = {}
    currentElement = len(getNeighboursOf(G, s))
    nextElement = 0
    deep = 0

    while queue.getQueueSize() != 0 and s != end:
        s = queue.dequeue()
        print(f"deep: {deep} | element: {s}")
        for neighbour in getNeighboursOf(G, s):
            if neighbour not in alreadyReachedElements:
                queue.enqueue(neighbour)
                if deep not in applicationReverseDict:
                    applicationReverseDict[deep] = []
                applicationReverseDict[deep].append((neighbour, s))
                nextElement += 1
                alreadyReachedElements.append(neighbour)

        currentElement -= 1
        if currentElement == 0 and s != end:
            currentElement = nextElement
            nextElement = 0
            deep += 1

    if s == end:
        deep -= 1
        path = []
        n = len(applicationReverseDict[deep])
        while s != start:
            i = 0
            finded = False
            while i < n and not finded:
                antecedant = applicationReverseDict[deep][i][0]
                image = applicationReverseDict[deep][i][1]
                if antecedant == s:
                    path.append(image)
                    s = image
                    finded = True
                    deep -= 1
                i += 1
        path.reverse()
        path.append(end)
        return path

    else: # There is not solution
        return None

def parcourProfondeur(G, sommet, markedSommets, deep):
    print(f"deep: {deep} | sommet: {sommet}")
    markedSommets.append(sommet)
    for neighbour in getNeighboursOf(G, sommet):
        if neighbour not in markedSommets:
            parcourProfondeur(G, neighbour, markedSommets, deep + 1)


if __name__ == "__main__":
    X = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
    U = [('A', 'C'), ('C', 'B'), ('C', 'D'), ('B', 'E'),
        ('D', 'G'), ('D', 'H'), ('E', 'G'),
        ('G', 'I'), ('H', 'I'), ('F', 'I'), ('F', 'J'),
        ('I', 'J')]
    G = (X, U)


    print(parcourLargeur(G, 'A', 'J'))
    print('-' * 15)
    print(parcourLargeurOpti(G, 'A', 'J'))
    print('-' * 15)
    parcourProfondeur(G, 'A', [], 0)
