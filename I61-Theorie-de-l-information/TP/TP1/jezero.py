import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
from time import time

import infoUtils

def registration(Im1cent, Im2array, niter=100, crop=200, depv=0, deph=0):
  # Im1cent: partie centrale de l'image 1 (2D np array)
  # Im2array: image 2 (2D np array)
  # niter: nombre d'itérations (default: 100)
  # crop: marge pour le déplacement (default: 200)
  # depv: déplacement vertical initial (default: 0)
  # deph: déplacement horizontal initial (default: 0)

  n = len(Im2array)
  flagMap = [0] * (n * n)
  flagMap[(crop + deph) * n + (crop + depv)] = 1

  # Itérer niter fois
  for i in range(niter):
      print(f'Iteration: {i}')
      print(f'Deplacement vertical: {depv}')
      print(f'Deplacement horizontal: {deph}')

      # Extraire la partie de l'image 2 centrée sur le déplacement
      # actuel et calculer la nmi
      Im2cent = Im2array[crop + deph - 1:-crop + depv + 1,crop + depv - 1:-crop + depv + 1]

      # Extraire chaque partie de l'image 2 décalée d'un pixel dans
      # chacune des 4 directions
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

      # Calculer l'information mutuelle normalisée entre l'image 1
      # et chacune des images décalées


      # Décider de la direction dans laquelle déplacer l'image et
      # incrémenter depv et deph d'un pixel en fonction
      maxNMI = max(max(nmiRight, nmiLeft), max(nmiUp, nmiDown))
      if (maxNMI == nmiRight):
          deph += 1
      elif(maxNMI == nmiLeft):
          deph -= 1
      elif(maxNMI == nmiUp):
          depv -= 1
      elif(maxNMI == nmiDown):
          depv += 1

      print(f"\t\tTHE CURRENT NMI = {maxNMI}")

  return Im2cent, [], depv, deph

if __name__ == "__main__":
    Im1 = Image.open('Jezero1.tif')
    Im2 = Image.open('Jezero2.tif')

    Im1array = np.asarray(Im1)
    Im2array = np.asarray(Im2)

    print(max(Im1array.max(), Im2array.max()))


    crop = 200

    # Partie centrale de l'image 1
    Im1cent = Im1array[crop:-crop,crop:-crop]
    plt.figure(1)
    plt.imshow(Im1cent)

    registration(Im1cent, Im2array)

    # Partie centrale de l'image 2
    Im2orig = Im2array[crop:-crop,crop:-crop]
    plt.figure(2)
    plt.imshow(Im2orig)

    # Différence entre les deux images
    Imdiff = Im1cent - Im2orig
    plt.figure(3)
    plt.imshow(abs(Imdiff))
    plt.colorbar()

    plt.show()

    print(registration(Im1cent, Im2array, niter=100, crop=200, depv=0, deph=0))
