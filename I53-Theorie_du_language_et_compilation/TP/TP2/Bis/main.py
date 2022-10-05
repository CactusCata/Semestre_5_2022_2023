import sys
import analLexical
import analSyntax

if __name__ == "__main__":
    sentence = sys.argv[1]
    lexicalsUnits = analLexical.analLex(sentence)
    analSyntax.analSyntax(lexicalsUnits)
    print()
