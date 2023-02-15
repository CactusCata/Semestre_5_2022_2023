import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

from math import log2

def getProbabilities(matrixImg):

    #plt.figure()
    #plt.imshow(matrixImg, cmap='gray')

    # Calculer et afficher la densité de probabilité de l'image
    xe = np.asarray(range(np.amax(matrixImg[:])+2))
    H1, xe = np.histogram(matrixImg.reshape(-1), bins=xe)
    P1 = H1/matrixImg.size
    #plt.figure()
    #plt.plot(P1)
    #plt.show()
    return P1

def getMatrixImg(img):
    Im = Image.open(img)
    Imarray = np.asarray(Im)
    return Imarray

def entropy(probabilities):
    sum = 0
    for proba in probabilities:
        if (proba != 0):
            sum += proba * log2(proba)
    return -sum

def conjointe(distribution1, distribution2, biggestValue=256):
    countList = [0] * (biggestValue * biggestValue)
    pairAmount = 0

    for line in range(biggestValue):
        for col in range(biggestValue):
            countList[distribution1[line][col] * biggestValue + distribution2[line][col]] += 1
            pairAmount += 1

    for line in range(biggestValue):
        for col in range(biggestValue):
            countList[line * biggestValue + col] /= pairAmount

    return countList

def NMI(distribution1, distribution2, biggestValue=256):
    probaD1 = getProbabilities(distribution1)
    probaD2 = getProbabilities(distribution2)

    entropyIm1 = entropy(probaD1)
    entropyIm2 = entropy(probaD2)

    conjointeIm1xIm2 = conjointe(distribution1, distribution2, biggestValue)
    entropyIm1xIm2 = entropy(conjointeIm1xIm2)

    IM1xIm2 = entropyIm1 + entropyIm2 - entropyIm1xIm2

    IMN = (2 * IM1xIm2) / (entropyIm1 + entropyIm2)

    return IMN
