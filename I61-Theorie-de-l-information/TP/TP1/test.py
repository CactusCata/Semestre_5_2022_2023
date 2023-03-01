import numpy as np
from PIL import Image
from time import time
import sys
import os

def get_entropy(distribution):
    copiedDistribution = np.copy(distribution)
    copiedDistribution[copiedDistribution == 0] = 1e-20
    logged = np.log2(copiedDistribution)
    product = np.multiply(distribution, logged)
    return -np.sum(product)

def conjointe(histo1, histo2, biggestValue=256):
    # Flatten the distributions and stack them vertically
    flat1 = histo1.flatten()
    flat2 = histo2.flatten()
    stacked = np.stack((flat1, flat2), axis=-1)

    # Compute the joint distribution using bincount and np.ravel_multi_index
    counts = np.bincount(np.ravel_multi_index(stacked.T, dims=(biggestValue, biggestValue)), minlength=biggestValue**2)
    joint = counts / counts.sum()

    return joint

def NMI(distribution1, imageMatrixHisto1, distribution2, imageMatrixHisto2, biggestValue=256):
    start = time()
    entropyIm1 = get_entropy(distribution1)
    print(f"entropyIm1:\t\t {time() - start}s")

    start = time()
    entropyIm2 = get_entropy(distribution2)
    print(f"entropyIm2:\t\t {time() - start}s")

    start = time()
    conjointeIm1xIm2 = conjointe(imageMatrixHisto1, imageMatrixHisto2, biggestValue)
    print(f"conjointeIm1xIm2:\t {time() - start}s")

    start = time()
    entropyIm1xIm2 = get_entropy(conjointeIm1xIm2)
    print(f"entropyIm1xIm2:\t\t {time() - start}s")


    IM_Im1xIm2 = entropyIm1 + entropyIm2 - entropyIm1xIm2

    nmi = (2 * IM_Im1xIm2) / (entropyIm1 + entropyIm2)

    return nmi

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
        nmi = compare_images(imageMatrix1, imageMatrix2, 200, 868)
        print(f"NMI done in {time() - start}s")
        print(f"NMI = {nmi}")
    else:
        print(f"Usage command: {sys.argv[0]} [test] to test")
        print(f"Usage command: {sys.argv[0]} [filename] [filename]")
