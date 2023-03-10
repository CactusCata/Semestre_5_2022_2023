from tkinter import messagebox

def get_list_serialized(sentence):
    sentence = sentence.replace("(", "").replace(")", "")
    pointsStr = sentence.split(":")
    points = []
    for pointStr in pointsStr:
        xyStr = pointStr.split(",")
        points.append((int(xyStr[0]), int(xyStr[1])))
    return points
