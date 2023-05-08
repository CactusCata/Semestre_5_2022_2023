import os
from spermwhale import Spermwhale
from typing import List

def read_file_seq_alea(path):
    if not os.path.exists(path):
        print(f"Le fichier \"{path}\" n'existe pas")
        return []

    file = open(path, "r")
    file_lines = file.readlines()
    file.close()

    sequences = []

    for line in file_lines:
        line = [int(c) for c in line.rstrip().replace(',', '')[:50]]
        sequences.append(tuple(line))
    return sequences

def read_file_cachalots_properties(path):
    """
    Permet de lire et d'extraire les données d'un fichier
    d'observation de cachalot
    """
    if not os.path.exists(path):
        print(f"Le fichier \"{path}\" n'existe pas")
        return []
    
    file_trajectories = open(path, "r")
    file_content = file_trajectories.read()
    
    file_trajectories = file_content.split("\n\n\nTrajectoire_")
    spermwhales:List[Spermwhale] = []

    for file_trajectory in file_trajectories:
        file_lines = file_trajectory.split("\n")
        spermwhale = Spermwhale(file_lines[0])

        for file_line in file_lines[2:]:
            long, lat, depth, _, timestamp, _ = file_line.split(";")
            spermwhale.append(float(long), float(lat), float(depth), float(timestamp))
        spermwhales.append(spermwhale)
    return spermwhales