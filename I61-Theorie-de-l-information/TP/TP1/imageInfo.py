import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
from time import time

class ImageAlignment():

    def __init__(self, imageNameA, imageNameB):
        self.imageNameA = imageAName
        self.imageNameB = imageBName

        self.imageA = None
        self.imageB = None

        # matrice des pixels
        self.imageMatrixA = None
        self.imageMatrixB = None

        self.matrixDimensions = (0, 0)

        # crop value for crop image A and image B
        self.cropValue = 0

        # image cropped
        self.imageMatrixACropped = None
        self.imageMatrixBCropped = None

        # retiens les NMI pour chaque pos
        self.mapNMIPos = None

        # histogramme (valeur de pixel : occurence)
        self.currentHistogramPixels = None

    def loadImages(self):
        """
        Charge les images en mémoire
        """
        self.imageA = Image.open(self.imageNameA)
        self.imageB = Image.open(self.imageNameB)

    def loadNpMatrix(self):
        """
        Charge les matrices des images
        """
        self.imageMatrixA = np.asarray(self.imageA)
        self.imageMatrixB = np.asarray(self.imageB)

        self.matrixDimensions = self.imageMatrixB.shape
        self.mapNMIPos = [0] * (self.matrixDimensions[0] * self.matrixDimensions[1])

    def setCrop(self, cropValue):
        self.cropValue = cropValue

    def cropImageMatrixA(self):
        """
        Crop l'image A
        """
        self.imageMatrixACropped = self.imageMatrixA[self.crop:-self.crop,self.crop:-self.crop]

    def cropImageMatrixB(self, depv, deph):
        """
        Image cropped en (-1, +1) en x et en y
        """
        self.imageMatrixBCropped = self.imageMatrixA[
                                    self.crop + deph - 1:-self.crop + deph + 1,
                                    self.crop + depv - 1:-self.crop + depv + 1]

    def initDefaultHistogramImageB(self):
        self.currentHistogramPixels = [0] * (self.matrixDimensions[0] * self.matrixDimensions[1])
        for line in range(self.matrixDimensions[0]):
            for col in range(self.matrixDimensions[1]):
                self.currentHistogramPixels[self.imageMatrixACropped[line,col] * self.matrixDimensions[0] + self.imageMatrixBCropped[line,col]] += 1

    def moveImageB(self, currentX, currentY, dM, axeName):
        imageMatrixBCoppedMoved = self.imageMatrixBCropped
        toAdd = None
        toRemove = None
        if (axeName == "X"):
            if (dM > 0): # on the left
                toAdd = self.imageMatrixBCropped[-1:,:]
                toRemove = self.imageMatrixBCropped[:1,:]
            elif (dM < 0): # on the right
                toAdd = self.imageMatrixBCropped[:1,:]
                toRemove = self.imageMatrixBCropped[-1:,:]
        elif (axeName == "Y"):
            if (dM > 0): # on the up
                toAdd = self.imageMatrixBCropped[:,:1]
                toRemove = self.imageMatrixBCropped[:,-1:]
            elif (dM < 0):
                toAdd = self.imageMatrixBCropped[:,-1:]
                toRemove = self.imageMatrixBCropped[:,:-1]

        return (toAdd, toRemove)

    def registration(niter=100, depv=0, deph=0):
        # Im1cent: partie centrale de l'image 1 (2D np array)
        # Im2array: image 2 (2D np array)
        # niter: nombre d'itérations (default: 100)
        # crop: marge pour le déplacement (default: 200)
        # depv: déplacement vertical initial (default: 0)
        # deph: déplacement horizontal initial (default: 0)

        self.cropImageMatrixB(depv, deph)
        self.initDefaultHistogramImageB()


        for i in range(niter):

            nmiRight = 0
            nmiLeft = 0
            nmiUp = 0
            nmiDown = 0

            if (not flagMap[(crop + deph + 1) * n + (crop + depv)]):
                right = Im2cent[1:,1:-1]
                start = time()
                nmiRight = infoUtils.NMI(Im1cent, right, 867)
                print(f"nmi calculus =  {time() - start}")
                print(f"nmi right = {nmiRight}")
                flagMap[(crop + deph + 1) * n + (crop + depv)] = 1

            if (not flagMap[(crop + deph - 1) * n + (crop + depv)]):
                left = Im2cent[:-1,1:-1]
                nmiLeft = infoUtils.NMI(Im1cent, left, 867)
                print(f"nmi left = {nmiLeft}")
                flagMap[(crop + deph - 1) * n + (crop + depv)] = 1

            if (not flagMap[(crop + deph) * n + (crop + depv - 1)]):
                up = Im2cent[1:-1,:-1]
                nmiUp = infoUtils.NMI(Im1cent, up, 867)
                print(f"nmi up = {nmiUp}")
                flagMap[(crop + deph) * n + (crop + depv - 1)] = 1

            if  (not flagMap[(crop + deph) * n + (crop + depv + 1)]):
                down = Im2cent[1:-1,1:]
                nmiDown = infoUtils.NMI(Im1cent, down, 867)
                print(f"nmi down = {nmiDown}")
                flagMap[(crop + deph) * n + (crop + depv + 1)] = 1
