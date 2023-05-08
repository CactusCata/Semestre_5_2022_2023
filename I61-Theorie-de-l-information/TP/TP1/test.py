import numpy as np
from PIL import Image
from time import time
import sys
import os
from sortedList import SortedList

def get_entropy(distribution):
    copiedDistribution = np.copy(distribution)
    copiedDistribution[copiedDistribution == 0] = 1e-20
    logged = np.log2(copiedDistribution)
    product = np.multiply(distribution, logged)
    return -np.sum(product)

def conjointe(imageMatrix1, imageMatrix2, biggestValue=256):
    # Flatten the distributions and stack them vertically
    flat1 = imageMatrix1.flatten()
    flat2 = imageMatrix2.flatten()
    stacked = np.stack((flat1, flat2), axis=-1)

    # Compute the joint distribution using bincount and np.ravel_multi_index
    counts = np.bincount(np.ravel_multi_index(stacked.T, dims=(biggestValue, biggestValue)), minlength=biggestValue**2)
    joint = counts / counts.sum()

    return joint

def NMI(distribution1, imageMatrix1, distribution2, imageMatrix2, biggestValue=256):
    entropyIm1 = get_entropy(distribution1)
    entropyIm2 = get_entropy(distribution2)

    conjointeIm1xIm2 = conjointe(imageMatrix1, imageMatrix2, biggestValue)
    entropyIm1xIm2 = get_entropy(conjointeIm1xIm2)

    IM_Im1xIm2 = entropyIm1 + entropyIm2 - entropyIm1xIm2

    nmi = (2 * IM_Im1xIm2) / (entropyIm1 + entropyIm2)

    return nmi

def search_best_shift(imageMatrix1, imageMatrix2, crop, maxValue, iteration=100):
    binsSequence = [x for x in range(maxValue + 1)]
    imageMatrix1Cropped = imageMatrix1[crop:-crop,crop:-crop]
    imageMatrix1Cropped = imageMatrix1.flatten()
    imageMatrixDistribution1, _ = np.histogram(imageMatrix1Cropped, bins=binsSequence, density=True)

    activeNMI = SortedList(0)
    imageMatrix2Cropped = imageMatrix2[crop:-crop,crop:-crop]
    imageMatrix2Cropped = imageMatrix2.flatten()
    imageMatrixDistribution2, _ = np.histogram(imageMatrix2Cropped, bins=binsSequence, density=True)
    nmi = NMI(imageMatrixDistribution1, imageMatrix1Cropped, imageMatrixDistribution2, imageMatrix2Cropped, maxValue)
    activeNMI.append((nmi, (0, 0)))

    for i in range(iteration):
        bestNMIInfo = activeNMI.array[-1]
        bestNMIPos = bestNMIInfo[1]
        print(f"Best pos is: {bestNMIPos} with NMI = {bestNMIInfo[0]}")
    
        for mvt in {(-1, 0), (1, 0), (0, -1), (0, 1)}:
            dx = bestNMIPos[0] + mvt[0]
            dy = bestNMIPos[1] + mvt[1]
            imageMatrix2Cropped = imageMatrix2[crop+dx:-crop+dx,crop+dy:-crop+dy]
            imageMatrix2Cropped = imageMatrix2.flatten()
            imageMatrixDistribution2, _ = np.histogram(imageMatrix2Cropped, bins=binsSequence, density=True)
            nmi = NMI(imageMatrixDistribution1, imageMatrix1Cropped, imageMatrixDistribution2, imageMatrix2Cropped, maxValue)
            print(f"NMI for {(dx, dy)} = {nmi}")
            activeNMI.append((nmi, (dx, dy)))

        

def compare_images(imageMatrix1, imageMatrix2, crop, maxValue):
    if (crop != 0):
        imageMatrix1 = imageMatrix1[crop:-crop,crop:-crop]
        imageMatrix2 = imageMatrix2[crop:-crop,crop:-crop]

    imageMatrix1 = imageMatrix1.flatten()
    imageMatrix2 = imageMatrix2.flatten()

    start = time()
    binsSequence = [x for x in range(maxValue + 1)]
    imageMatrixDistribution1, _ = np.histogram(imageMatrix1, bins=binsSequence, density=True)
    imageMatrixDistribution2, _ = np.histogram(imageMatrix2, bins=binsSequence, density=True)

    print(f"loading time:\t\t {time() - start}")

    return NMI(imageMatrixDistribution1, imageMatrix1, imageMatrixDistribution2, imageMatrix2, maxValue)


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "test":
        print(f"Try test...")
        imageMatrix1 = np.array([
            [0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0],
            [0, 0, 1, 1, 1, 0, 0],
            [0, 0, 1, 2, 1, 0, 0],
            [0, 0, 1, 1, 1, 0, 0],
            [0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0]
        ])

        imageMatrix2 = np.array([
            [2, 2, 2, 2, 2, 2, 2],
            [2, 2, 2, 2, 2, 2, 2],
            [2, 2, 0, 0, 0, 2, 2],
            [2, 2, 0, 1, 0, 2, 2],
            [2, 2, 0, 0, 0, 2, 2],
            [2, 2, 2, 2, 2, 2, 2],
            [2, 2, 2, 2, 2, 2, 2]
        ])
        nmi = compare_images(imageMatrix1, imageMatrix2, 0, 3)
        print(f"NMI = {nmi}")
    elif len(sys.argv) > 2:
        imgName1 = sys.argv[1]
        imgName2 = sys.argv[2]
        if (not os.path.exists(imgName1)):
            print(f"The file {imgName1} do not exist")
            exit()

        if (not os.path.exists(imgName2)):
            print(f"The file {imgName2} do not exist")
            exit()

        image1 = Image.open(imgName1)
        image2 = Image.open(imgName2)
        imageMatrix1 = np.asarray(image1)
        imageMatrix2 = np.asarray(image2)
        start = time()
        print(f"Usualy NMI = {compare_images(imageMatrix1, imageMatrix2, 200, 868)}")
        nmi = search_best_shift(imageMatrix1, imageMatrix2, 200, 868)
        print(f"NMI done in {time() - start}s")
        print(f"NMI = {nmi}")
    else:
        print(f"Usage command: {sys.argv[0]} [test] to test")
        print(f"Usage command: {sys.argv[0]} [filename] [filename]")
