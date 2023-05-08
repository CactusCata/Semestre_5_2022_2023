from random import random, randint, uniform
from math import sin, pi
import matplotlib.pyplot as plt
import numpy as np

def generate_abscisse(x_start, x_end, x_step):
    """
    Génère une abscisse de x_start à x_end avec x_step nombre
    de valeurs différentes réparties équitablement
    """
    x_array = []
    x = x_start
    pas_x = (x_end - x_start) / x_step
    while x <= x_end:
        x_array.append(x)
        x += pas_x
    return x_array

def uniform_signal(x_start=0, x_end=20, x_step=200):
    x_array = generate_abscisse(x_start, x_end, x_step)

    signal_array = []
    for x in x_array:
        signal_array.append(10 + random())
    return x_array, signal_array


def random_signal(random_signal_amount=20, x_start=0, x_end=20, x_step=200):
    coefs_sin = []
    for i in range(random_signal_amount):
        coefs_sin.append(uniform(-pi/2, pi/2))

    x_array = generate_abscisse(x_start, x_end, x_step)

    signal_array = []
    for x in x_array:
        sum = 0
        for coef_sin in coefs_sin:
            sum += sin(2 * pi * coef_sin * x)
        signal_array.append(sum / random_signal_amount)

    return x_array, signal_array

def quantification_to_equals_classes(signal_array, class_amount=8):
    max_value = max(signal_array)
    min_value = min(signal_array)

    histogram_x = []
    pas_x = (max_value - min_value) / class_amount
    x = min_value
    while x <= max_value:
        histogram_x.append(x)
        x += pas_x

    print(histogram_x)
    
    histogram = [0] * len(histogram_x)
    for signal_value in signal_array:
        for i in range(len(histogram_x) - 1):
            if (histogram_x[i] <= signal_value < histogram_x[i+1]):
                histogram[i] += 1
    
    return histogram_x, histogram

if __name__ == "__main__":
    x_array, signal_array = random_signal()

    histogram_x_a, histogram_a = quantification_to_equals_classes(signal_array, class_amount=10)
    
    plt.subplot(1, 2, 1)
    plt.plot(x_array, signal_array)

    plt.subplot(1, 2, 2)
    plt.step(histogram_x_a, histogram_a, color='r')
    plt.show()
