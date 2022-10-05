cc = 0
arrayLexUnits = []

def getLexUnit():
    if cc < len(arrayLexUnits):
        return arrayLexUnits[cc]
    else:
        return ['?', '?']

def increaseCC():
    global cc
    cc += 1

def A():
    unit = TYPE()
    unit2 = P()
    if (unit2 != None):
        writeMessagePart(f"sur pointeur")
    writeMessagePart(f"sur {unit[1]}")


def TYPE():
    unit = getLexUnit()
    if (unit[0] != "type"):
        throwError()
    increaseCC()
    return unit

def P():
    unit = getLexUnit()
    if unit[0] == "pointor":
        increaseCC()
        unit2 = P()
        if (unit2 != None):
            writeMessagePart(f"sur pointeur")
        return unit
    else:
        T_1()

def T_1():
    I()
    T_2()

def T_2():
    unit = getLexUnit()
    if (unit[0] == "bracket_square_left"):
        increaseCC()
        writeMessagePart(f"tableau")
        NB()
        unit = getLexUnit()
        if unit[0] != "bracket_square_right":
            throwError()
        increaseCC()
        T_2()

def I():
    unit = getLexUnit()
    if (unit[0] == "bracket_left"):
        increaseCC()
        unit2 = P()
        if unit2 != None:
            writeMessagePart(f"sur pointeur")
        unit = getLexUnit()
        if (unit[0] != "bracket_right"):
            throwError()
        increaseCC()
    else:
        ID()

def ID():
    unit = getLexUnit()
    if (unit[0] != "name"):
        throwError()
    increaseCC()

def NB():
    unit = getLexUnit()
    if (unit[0] != "number"):
        throwError()
    increaseCC()
    writeMessagePart(f"de {unit[1]}")

def throwError():
    print(f"Syntax error on character '{getLexUnit()[1]}'")
    exit(0)

def writeMessagePart(sentence):
    print(sentence, end=' ')

def analSyntax(arrayOfLexicalsUnits):
    global arrayLexUnits
    arrayLexUnits = arrayOfLexicalsUnits
    A()

    if (cc != len(arrayLexUnits)):
        print("end")
        throwError()
