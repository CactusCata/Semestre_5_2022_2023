#include "utils_unit.h"

void callAllTest_utils() {
    getNextIntFromLine_test();
    getAllIntInLine_test();
    appendText_test();
    writeNTimes_test();
    throwMallocErrorIfTrue_test();
}

void getNextIntFromLine_test() {
    setTestFunctionName("getNextIntFromLine");
    unsigned int cursor;
    int res;

    cursor = 0;
    setTestFunctionParameters("%s %d", "23 test 73 !!", cursor);
    res = getNextIntFromLine("23 test 73 !!", &cursor);
    intEqual(res, 23);


    
    cursor = 0;
    setTestFunctionParameters("%s %d", "", cursor);
    res = getNextIntFromLine("", &cursor);
    intEqual(res, -1);

    cursor = 2;
    setTestFunctionParameters("%s %d", "az863bonsoir !", cursor);
    res = getNextIntFromLine("az863bonsoir !", &cursor);
    intEqual(res, 863);

    cursor = 2;
    setTestFunctionParameters("%s %d", "1234567", cursor);
    res = getNextIntFromLine("1234567", &cursor);
    intEqual(res, 34567);
    
}

void getAllIntInLine_test() {
    setTestFunctionName("getAllIntInLine");
    int *res;

    setTestFunctionParameters("%s %d", "23 46 76 1259", 3);
    res = getAllIntInLine("23 46 76 1259", 3);
    int expected1[] = {23, 46, 76, 1259};
    intArrayEqual(res, expected1, 3);
    free(res);

    setTestFunctionParameters("%s %d", "0 1 2 3 4 5 6 7 8 9", 10);
    res = getAllIntInLine("0 1 2 3 4 5 6 7 8 9", 10);
    int expected2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    intArrayEqual(res, expected2, 10);
    free(res);

    setTestFunctionParameters("%s %d", "", 0);
    res = getAllIntInLine("", 0);
    int expected3[] = {};
    intArrayEqual(res, expected3, 0);
    free(res);

}

void appendText_test() {
    setTestFunctionName("appendText");
    int cursor = 0;

    cursor = 3;
    char base1[] = "Bonjour !";
    char add1[] = "soir";
    setTestFunctionParameters("%s %s %d", base1, add1, cursor);
    appendText(base1, add1, &cursor);
    stringEqual(base1, "Bonsoir");

    cursor = 3;
    char base2[] = "Bonsoir";
    char add2[] = "";
    setTestFunctionParameters("%s %s %d", base2, add2, cursor);
    appendText(base2, add2, &cursor);
    stringEqual(base2, "Bon");

}

void writeNTimes_test() {
    setTestFunctionName("writeNTimes");
    int cursor;
    char toRepeat;

    cursor = 5;
    toRepeat = 'x';
    char text1[] = "test:        ";
    setTestFunctionParameters("%s %d %c %d", text1, cursor, toRepeat, 6);
    writeNTimes(text1, &cursor, toRepeat, 6);
    stringEqual(text1, "test:xxxxxx  ");

    cursor = 3;
    toRepeat = '?';
    char text2[] = "BONSOIR !";
    setTestFunctionParameters("%s %d %c %d", text2, cursor, toRepeat, 0);
    writeNTimes(text2, &cursor, toRepeat, 0);
    stringEqual(text2, "BONSOIR !");

}

void throwMallocErrorIfTrue_test() {
    // We don't need that
}