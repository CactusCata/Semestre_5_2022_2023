lexicalsUnits = []
cc = 0

arrayOfInstructions = []

def getLexicalUnit():
    return lexicalsUnits[cc]

def expr_1():
    NOP()
    expr_2()

def expr_2():
    global cc
    # OU ou ET
    lexicalUnit = getLexicalUnit()
    if (lexicalUnit[0] == "CONNECTOR"):
        cc += 1
        NOP()
        arrayOfInstructions.append(lexicalUnit)

def NOP():
    global cc
    # NON
    lexicalUnit = getLexicalUnit()
    if (lexicalUnit[0] == "NEGAT"):
        cc += 1
        arrayOfInstructions.append(lexicalUnit)
        PAR()
    else:
        PAR()

def PAR():
    global cc
    # parentheses
    lexicalUnit = getLexicalUnit()
    if (lexicalUnit[0] == "PAR_L"):
        c += 1
        expr_1()
        lexicalUnit = getLexicalUnit()
        if (lexicalUnit[0] != "PAR_R"):
            print("Syntax error, a bracket was waited")
            exit(0)
        cc += 1
    else:
        BOOL()

def BOOL():
    global cc

    lexicalUnit = getLexicalUnit()
    if (lexicalUnit[0] != "BOOL"):
        print("Syntax error, a bool was waited")
        exit(0)
    cc += 1
    arrayOfInstructions.append(lexicalUnit)

def axiome(arrayOfLexicalsUnits):
    global lexicalsUnits

    lexicalsUnits = arrayOfLexicalsUnits
    expr_1()

    if (cc != len(lexicalsUnits)):
        print("Error syntax")
        exit(0)
    else:
        print("Good !")

def getArrayOfInstructions():
    return arrayOfInstructions
