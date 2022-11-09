#include "compregex.h"

// Variable globale de l'ER en train d'être lue
static char *text;
static int cursor;

// Variable globale de l'ER sous la forme d'une pile, prete à être évaluée
static char *textStack;
static int cursorStack;

/**
 * @brief E1 -> C1E2
 * 
 */
void E1() {
    C1();
    E2();
}

/**
 * @brief E2 -> +C1E2 | &
 * 
 */
void E2() {
    char c = getCurrentCharacter();
    if (c == '+') {
        // Détection du plus
        cursor++;
        C1();
        E2();
        addToTextStack('+');
    }
}

/**
 * @brief C1 -> KC2
 * 
 */
void C1() {
    K();
    C2();
}

/**
 * @brief C2 -> KC' | &
 * 
 */
void C2() {
    char c = getCurrentCharacter();
    if ((c >= 'a' && c <= 'z') || c == '(' || c == '{' || c == '[') {
        K();
        C2();
        addToTextStack('.');
    }
    /*
    char c = getCurrentCharacter();
    if (c == '.') {
        // Détection de concaténation
        cursor++;
        K();
        C2();
        addToTextStack('.');
    }
    */
}

/**
 * @brief K -> P* | P
 * 
 */
void K() {
    int cursorBeforeBStack = cursorStack;
    P();
    if(getCurrentCharacter() == '*') {
        cursor++;
        // Détection de l'étoile de Kleene
        addToTextStack('*');
    } else if (getCurrentCharacter() == '{') {
        cursor++;
        unsigned int cursorCopy = cursor; 
        int times = getNextIntFromLine(text, &cursorCopy);
        cursor = cursorCopy;

        if (times == -1) {
            throwSyntaxError("Entier attendu");
        }

        int currentCursorValueStack = cursorStack;
        char buffer[1024];
        int i = cursorBeforeBStack;
        for (; i < currentCursorValueStack; i++) {
            buffer[i] = textStack[i];
        }
        buffer[i++] = '\0';

        for (int j = 1; j < times; j++) {
            appendText(textStack, buffer, &cursorStack);
            addToTextStack('.');
        }

        if (getCurrentCharacter() != '}')  {
            throwSyntaxError("Accolade fermante attendue");
        }

        cursor++;

    }
}

void R() {
    char c = getCurrentCharacter(); 
    if (c >= 'a' && c <= 'z') {
        addToTextStack(c);
        addToTextStack('+');
        cursor++;
        R();
    }
}

/**
 * @brief P -> (E) | letter
 * 
 */
void P() {
    if (getCurrentCharacter() == '(') {
        cursor++;
        E1();
        if (getCurrentCharacter() != ')') {
            throwSyntaxError("Caractère de type parenthèse fermante attendu");
        }
        cursor++;
    } else if (getCurrentCharacter() == '[') { 
        cursor++;
        letter();
        R();

        if (getCurrentCharacter() != ']') {
            throwSyntaxError("Caractère ']' attendu");
        }
        cursor++;
    } else {
        letter();
    }
}

/**
 * @brief letter -> [a-z]
 * 
 */
void letter() {
    char c = getCurrentCharacter();
    if (c >= 'a' && c <= 'z') {
        cursor++;
        // Détection d'une lettre
        addToTextStack(c);
    } else {
        throwSyntaxError("Caractère de type lettre attendu");
    }
}

/**
 * @brief Construit sous forme de pile l'expression réguilère fournie
 * 
 * @param re l'expression réguilière
 */
void buildStackText(char *re) {
    cursor = 0; 
    text = re;
    cursorStack = 0;
    textStack = malloc(sizeof(char) * 2048);

    E1();

    if (cursor > strlen(text) || text[cursor] != '\0') {
        throwSyntaxError("Out of bounds");
    }

}

/**
 * @brief Détermine la caractère courant de l'ER lue.
 * 
 * @return char le caractère courant de l'ER
 */
char getCurrentCharacter() {
    return text[cursor];
}

/**
 * @brief Utilisé si une erreur de syntaxe est détectée
 * 
 * @param errorMsg Information supplémentaire sur la nature de l'erreur de syntaxe
 */
void throwSyntaxError(char *errorMsg) {
    printf("%s", errorMsg);
    printf(" à l'indice %d mais le caractère trouvé est: '%c'.\n", cursor, text[cursor]);

    if (textStack != NULL) {
        free(textStack);
    }

    exit(1);
}

/**
 * @brief Ajoute un élément à la pile
 * 
 * @param c caractère à ajouter
 */
void addToTextStack(char c) {
    textStack[cursorStack++] = c;
    textStack[cursorStack] = '\0';
}

/**
 * @brief Construit un afn à partir d'une expression réguilière
 * 
 * @param re l'expression réguilère
 * @return AFN l'afn reconnaissant le langage de l'ER
 */
AFN buildAFNFromRE(char *re) {
    buildStackText(re);

    //printf("La pile vaut \"%s\"\n", textStack);

    AFN *afnStack = (AFN *) malloc(sizeof(AFN *) * strlen(textStack));
    int afnStackCursor = 0;
    int reCursor = 0;

    while (textStack[reCursor] != '\0') {
        char c = textStack[reCursor];

        if (c >= 'a' && c <= 'z') {
            AFN afnLetter;
            afn_char(&afnLetter, c);
            afnStack[afnStackCursor++] = afnLetter;
        } else if (c == '.') {
            AFN afnConcat;
            afn_concat(&afnConcat, afnStack[afnStackCursor - 2], afnStack[afnStackCursor - 1]);
            afn_free(afnStack[afnStackCursor - 2]);
            afn_free(afnStack[afnStackCursor - 1]);
            afnStackCursor -= 2;
            afnStack[afnStackCursor++] = afnConcat;
        } else if (c == '+') {
            AFN afnUnion;
            afn_union(&afnUnion, afnStack[afnStackCursor - 2], afnStack[afnStackCursor - 1]);
            afn_free(afnStack[afnStackCursor - 2]);
            afn_free(afnStack[afnStackCursor - 1]);
            afnStackCursor -= 2;
            afnStack[afnStackCursor++] = afnUnion;
        } else if (c == '*') {
            AFN afnKleene;
            afn_kleene(&afnKleene, afnStack[afnStackCursor - 1]);
            afn_free(afnStack[afnStackCursor - 1]);
            afnStackCursor--;
            afnStack[afnStackCursor++] = afnKleene;
        }

        reCursor++;
    }

    free(textStack);
    AFN res = afnStack[0];
    free(afnStack);
    return res;

}