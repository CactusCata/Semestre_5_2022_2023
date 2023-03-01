from imageInfo import ImageAlignment

if __name__ == "__main__":
    ia = ImageAlignment("Jezero1.tif", "Jerezo2.tif")

    ia.loadImages()
    ia.loadNpMatrix()
    ia.setCrop(200)
    ia.cropImageMatrixA()