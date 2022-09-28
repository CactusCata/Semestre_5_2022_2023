import sys
import syntaxAnalyser
import threeAddressCode

def isString(s, startIndex, stringWanted):
    for i in range(len(stringWanted)):
        if (s[i + startIndex] != stringWanted[i]):
            return False
    return True

def analex(s):
    arrayOfLexicalsUnits = []
    i = 0
    while i < len(s):
        if (isString(s, i, "VRAI")):
            i += 4
            arrayOfLexicalsUnits.append(["BOOL", "VRAI", "True"])
        elif (isString(s, i, "FAUX")):
            i += 4
            arrayOfLexicalsUnits.append(["BOOL", "FAUX", "False"])
        elif (isString(s, i, "OU")):
            i += 2
            arrayOfLexicalsUnits.append(["CONNECTOR", "OU", "or"])
        elif (isString(s, i, "ET")):
            i += 2
            arrayOfLexicalsUnits.append(["CONNECTOR", "ET", "and"])
        elif (isString(s, i, "NON")):
            i += 3
            arrayOfLexicalsUnits.append(["NEGAT", "NON", "not"])
        elif (s[i] == '('):
            arrayOfLexicalsUnits.append(["PAR_L", "(", "("])
        elif (s[i] == ')'):
            arrayOfLexicalsUnits.append(["PAR_R", ")", ")"])
        else:
            print(f"Error, unknow char {s[i]} (col {i})")
            exit(0)
        i += 1

    return arrayOfLexicalsUnits

if __name__ == "__main__":
    print(sys.argv[1])
    arrayOfLexicalsUnits = analex(sys.argv[1])
    print(arrayOfLexicalsUnits)
    syntaxAnalyser.axiome(arrayOfLexicalsUnits)
    print(syntaxAnalyser.getArrayOfInstructions())
    threeAddressCode.createThreeAddressCode(syntaxAnalyser.getArrayOfInstructions())
