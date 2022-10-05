type = {"TYPE": ["char", "int", "float"]}

def isCorrect(sentence, sentenceWanted, index):
    for i in range(len(sentenceWanted)):
        if (sentence[i + index] != sentenceWanted[i]):
            return False
    return True


def analLex(sentence):
    arrayOfLexicalsUnits = []

    i = 0
    n = len(sentence)
    while i < n:
        if (isCorrect(sentence, "char", i)):
            arrayOfLexicalsUnits.append(["type", "char"])
            i += 4
        elif (isCorrect(sentence, "int", i)):
            arrayOfLexicalsUnits.append(["type", "int"])
            i += 3
        elif (isCorrect(sentence, "float", i)):
            arrayOfLexicalsUnits.append(["type", "float"])
            i += 5
        elif (isCorrect(sentence, "*", i)):
            arrayOfLexicalsUnits.append(["pointor", "*"])
        elif (sentence[i] >= 'a' and sentence[i] <= 'z'):
            arrayOfLexicalsUnits.append(["name", sentence[i]])
        elif (sentence[i] == '['):
            arrayOfLexicalsUnits.append(["bracket_square_left", '['])
        elif (sentence[i] == ']'):
            arrayOfLexicalsUnits.append(["bracket_square_right", ']'])
        elif (sentence[i] == '('):
            arrayOfLexicalsUnits.append(["bracket_left", '('])
        elif (sentence[i] == ')'):
            arrayOfLexicalsUnits.append(["bracket_right", ')'])
        elif ('0' <= sentence[i] <= '9'):
            arrayOfLexicalsUnits.append(["number", sentence[i]])
        else:
            print(f"Unknow character {sentence[i]}.")
            exit(0)
        i += 1
    return arrayOfLexicalsUnits
