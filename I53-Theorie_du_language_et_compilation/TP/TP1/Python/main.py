import dis
from time import time

# ============
# = Prologue =
# ============

def hello():
    print("Hello world")

def prologue():
    # On peut noter qu'il y a une différence entre l'affichage
    # maison et celui du pdf du prof: celui du prof comporte
    # des espaces de 3 et de 2 dans mon cas.  
    dis.dis(hello)

# ==============
# = Question 1 =
# ==============

def question1():
    # Question: Quels sont les noms des operations arithmetiques elementaires?
    #
    # Les noms des opérateurs arithmétiques élémentaires en Python sont:
    #   - BINARY_ADD (+)
    #   - BINARY_SUBTRACT (-)
    #   - BINARY_MULTIPLY (x)
    #   - BINARY_TRUE_DIVIDE (/)

    print("Opérateur +")
    dis.dis("3 + int('2')")
    print("Opérateur -")
    dis.dis("3 - int('2')")
    print("Opérateur *")
    dis.dis("3 * int('2')")
    print("Opérateur /")
    dis.dis("3 / int('2')")

# ==============
# = Question 2 =
# ==============

def part2_1():
    x = -1
    if (2 < 5):
        x = 0
    elif (2 > 1):
        x = 1
    else:
        x = 2

def part2_2():
    x = -1
    if (2 < 5):
        x = 0
    else:
        if (2 > 1):
            x = 1
        else:
            x = 2

def question2():
    # Question: Comparer les instructions de type 
    # if-elif-else avec des structures semantiquement equivalentes utilisant 
    # seulement des if-else imbriquees.
    # 
    # Réponse: Les deux structures sont équivalentes au vus de la sortie
    # en assembleur.
    # Cela peut s'expliquer par le fait que, quelque part dans l'étape de
    # compilation, l'instruction elif est remplacée par un else if

    print("Structure avec if-elif-else:")
    dis.dis(part2_1)
    print("Structure avec uniquement les instructions if et else")
    dis.dis(part2_2)

# ==============
# = Question 3 =
# ==============

def part3_1():
    start = time()

    i = 0
    while i < 10_000_000:
        i += 1

    end = time() - start
    return end

def part3_2():
    start = time()

    for i in range(10_000_000):
        pass

    end = time() - start
    return end

def question3():
    # Question: Comparer les temps d'execution des boucles for et while.
    # Comment justier cette difference?
    # 
    # Réponse: 
    # [Boucle while] 
    #   - Commence ligne 84 et se termine ligne 86 (incluse)
    #   - Possède 11 instructions en assembleur
    # 
    # [Boucle for]
    #   - Commence ligne 94 et se termine ligne 95 (incluse)
    #   - Possède 7 instructions en assembleur
    # 
    # La différence de temps d'execution se justifie par un nombre 
    # réduit d'instruction en assembleur pour la boucle for.
    # De plus, la boucle for n'utilise pas d'incrémentation mais 
    # plutôt un système d'itérateur.

    timedPart3_1 = part3_1()
    timedPart3_2 = part3_2()
    print(f"Temps de calcul pour la boucle while: {timedPart3_1:.2f} sec")
    print(f"Temps de calcul pour la boucle for: {timedPart3_2:.2f} sec")
    print(f"La boucle for est {timedPart3_2 * 100 / timedPart3_1:.2f}% plus efficace que la boucle while")

    print("Affichage des instructions en assembleur pour la boucle while:")
    dis.dis(part3_1)

    print("Affichage des instructions en assembleur pour la boucle for:")
    dis.dis(part3_2)

# ==============
# = Question 4 =
# ==============

def question4():
    print(">> Instructions en assembleur pour la liste en compréhension:")
    dis.dis("[i for i in range(10)]")
    print()
    print(">> Instructions en assembleur pour la liste en extension:")
    dis.dis("[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]")


# ========
# = Main =
# ========

if __name__ == "__main__":
    #prologue()

    #question1()

    #question2()

    #question3()

    question4()
    
