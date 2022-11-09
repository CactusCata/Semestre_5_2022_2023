#include "arrayUtils_unit.h"

void callAllTest_arrayUtils() {
    charArrayContrains_test();
    copyArray_test();
    copyCharArray_test();
    fillIntArray_test();
    fillCharArray_test();
    shiftValuesArrayToRight_test();
    serializeArray_test();
    serializeSet_test();
    serializeContainer_test();
    printArrayChar_test();
    printArray_test();
    ajustArray_test();
    concatenateArrays_test();
    printMatrix_test();
    sortArray_test();
    unionCharArray_test();
}

void charArrayContrains_test() {
    setTestFunctionName("charArrayContrains");
    bool res;

    setTestFunctionParameters("%s %d %c", "bonsoir", 7, 'n');
    res = charArrayContrains("bonsoir", 7, 'n');
    boolEqual(res, true);

    setTestFunctionParameters("%s %d %c", "bonsoir", 7, 'x');
    res = charArrayContrains("bonsoir", 7, 'x');
    boolEqual(res, false);

    setTestFunctionParameters("%s %d %c", "", 0, '?');
    res = charArrayContrains("", 0, '?');
    boolEqual(res, false);
}

void copyArray_test() {
    setTestFunctionName("copyArray");
    int *res;

    int array1[] = {1, 2, 3};
    setTestFunctionParameters("{1,2,3} %d", 3);
    res = copyArray(array1, 3);
    intArrayEqual(res, array1, 3);
    free(res);

    int array2[] = {};
    setTestFunctionParameters("{} %d", 0);
    res = copyArray(array2, 0);
    intArrayEqual(res, array2, 0);
    free(res);

}

void copyCharArray_test() {
    setTestFunctionName("copyCharArray");
    char *res;

    char array1[] = {'a', 'b', 'c'};
    setTestFunctionParameters("{'a','b','c'} %d", 3);
    res = copyCharArray(array1, 3);
    charArrayEqual(res, array1, 3);
    free(res);

    char array2[] = {};
    setTestFunctionParameters("{} %d", 0);
    res = copyCharArray(array2, 0);
    charArrayEqual(res, array2, 0);
    free(res);

}

void fillIntArray_test() {
    setTestFunctionName("fillIntArray");

    int array1[] = {5, 3, -2, 99, 27};
    int expected1[] = {63, 63, 63, 63, 63};
    setTestFunctionParameters("{5,3,-2,99,27} %d %d", 5, 63);
    fillIntArray(array1, 5, 63);
    intArrayEqual(array1, expected1, 5);

    int array2[] = {};
    int expected2[] = {};
    setTestFunctionParameters("{} %d %d", 0, 50);
    fillIntArray(array2, 0, 50);
    intArrayEqual(array2, expected2, 0);

}

void fillCharArray_test() {
    setTestFunctionName("fillCharArray");

    char array1[] = {'a', 'b', 'c'};
    char expected1[] = {'?', '?', '?'};
    setTestFunctionParameters("{'a','b','c'} %d %c", 3, '?');
    fillCharArray(array1, 3, '?');
    charArrayEqual(array1, expected1, 3);

    char array2[] = {};
    char expected2[] = {};
    setTestFunctionParameters("{} %d %c", 0, '?');
    fillCharArray(array2, 0, '?');
    charArrayEqual(array2, expected2, 0);

    char array3[] = {'a'};
    char expected3[] = {'?'};
    setTestFunctionParameters("{'a'} %d %c", 1, '?');
    fillCharArray(array3, 1, '?');
    charArrayEqual(array3, expected3, 1);
}

void shiftValuesArrayToRight_test() {
    setTestFunctionName("shiftValuesArrayToRight");

    int array1[] = {1, 2, 3, 4, 5, 6, 7};
    int expected1[] = {1, 2, 3, 4, 4, 5, 6};
    setTestFunctionParameters("{1,2,3,4,5,6,7} %d %d", 7, 3);
    shiftValuesArrayToRight(array1, 7, 3);
    intArrayEqual(array1, expected1, 7);

    int array2[] = {1,2,3,4,5,6,7};
    int expected2[] = {1,2,3,4,5,6,7};
    setTestFunctionParameters("{1,2,3,4,5,6,7} %d %d", 7, 9);
    shiftValuesArrayToRight(array2, 7, 9);
    intArrayEqual(array2, expected2, 7);

    int array3[] = {};
    int expected3[] = {};
    setTestFunctionParameters("{} %d %d", 0, 3);
    shiftValuesArrayToRight(array3, 0, 9);
    intArrayEqual(array3, expected3, 0);

}

void serializeArray_test() {
    setTestFunctionName("serializeArray");
    char *res;

    int array1[] = {1,2,3,4,5,6};
    setTestFunctionParameters("{1,2,3,4,5,6} %d", 6);
    res = serializeArray(array1, 6);
    stringEqual(res, "[1, 2, 3, 4, 5, 6]");
    free(res);

    int array2[] = {1};
    setTestFunctionParameters("{1} %d", 1);
    res = serializeArray(array2, 1);
    stringEqual(res, "[1]");
    free(res);

    int array3[] = {};
    setTestFunctionParameters("{} %d", 1);
    res = serializeArray(array3, 0);
    stringEqual(res, "[]");
    free(res);
}

void serializeSet_test() {
    setTestFunctionName("serializeSet");
    char *res;

    int array1[] = {1,2,3,4,5,6};
    setTestFunctionParameters("{1,2,3,4,5,6} %d", 6);
    res = serializeSet(array1, 6);
    stringEqual(res, "{1, 2, 3, 4, 5, 6}");
    free(res);

    int array2[] = {1};
    setTestFunctionParameters("{1} %d", 1);
    res = serializeSet(array2, 1);
    stringEqual(res, "{1}");
    free(res);

    int array3[] = {};
    setTestFunctionParameters("{} %d", 1);
    res = serializeSet(array3, 0);
    stringEqual(res, "{}");
    free(res);
}

void serializeContainer_test() {
    setTestFunctionName("serializeContainer");
    char *res;

    int array1[] = {1,2,3,4,5,6};
    setTestFunctionParameters("{1,2,3,4,5,6} %d", 6);
    res = serializeContainer(array1, 6, '?', '!');
    stringEqual(res, "?1, 2, 3, 4, 5, 6!");
    free(res);

    int array2[] = {1};
    setTestFunctionParameters("{1} %d", 1);
    res = serializeContainer(array2, 1, '?', '!');
    stringEqual(res, "?1!");
    free(res);

    int array3[] = {};
    setTestFunctionParameters("{} %d", 1);
    res = serializeContainer(array3, 0, '?', '!');
    stringEqual(res, "?!");
    free(res);
}

void printArrayChar_test() {

}

void printArray_test() {

}

void ajustArray_test() {
    setTestFunctionName("ajustArray");

    int *array1 = (int *) malloc(sizeof(int) * 14);
    array1[0] = 2;
    array1[1] = 3;
    array1[2] = 5;
    array1[3] = 7;
    array1[4] = 11;
    setTestFunctionParameters("{2,3,5,7,11,...} %d", 3);
    int *res1 = ajustArray(array1, 3);
    int expected1[] = {2, 3, 5};
    intArrayEqual(res1, expected1, 3);
    free(res1);

    int *array2 = (int *) malloc(sizeof(int) * 14);
    array2[0] = 2;
    array2[1] = 3;
    array2[2] = 5;
    array2[3] = 7;
    array2[4] = 11;
    setTestFunctionParameters("{2,3,5,7,11,...} %d", 1);
    int *res2 = ajustArray(array2, 1);
    int expected2[] = {2};
    intArrayEqual(res2, expected2, 1);
    free(res2);


}

void concatenateArrays_test() {
    /*
    setTestFunctionName("concatenateArrays");

    int *array1a = (int *) malloc(sizeof(int) * 10);
    array1a[0] = 6;
    array1a[1] = 9;
    array1a[2] = -1;
    int array1b[] = {1, 4, 8, 10, 15, -1};
    setTestFunctionParameters("{6,9,-1} {1,4,8,10,15,-1} 10");
    concatenateArrays(array1a, array1b, 10);
    int expected1[] = {1, 4, 6, 8, 9, 10, 15, -1};
    intArrayEqual(array1a, expected1, 5);
    free(array1a);
    */

}

void printMatrix_test() {

}

void sortArray_test() {
    setTestFunctionName("sortArray");

    int array1[] = {9,6,7,3,4,2};
    setTestFunctionParameters("{9,6,7,3,4,2} %d", 6);
    sortArray(array1, 6);
    int expected1[] = {2, 3, 4, 6, 7, 9};
    intArrayEqual(array1, expected1, 6);

    int array2[] = {};
    setTestFunctionParameters("{} %d", 0);
    sortArray(array2, 0);
    int expected2[] = {};
    intArrayEqual(array2, expected2, 0);

    int array3[] = {-15};
    setTestFunctionParameters("{-15} %d", 1);
    sortArray(array3, 1);
    int expected3[] = {-15};
    intArrayEqual(array3, expected3, 1);

}

void unionCharArray_test() {
    setTestFunctionName("unionCharArray");

    setTestFunctionParameters("%s %d %s %d", "abc", 3, "gchijk", 6);
    char *res1 = unionCharArray("abc", 3, "gchijk", 6);
    charArrayEqual(res1, "abcghijk", 8);
    free(res1);

    setTestFunctionParameters("%s %d %s %d", "a", 1, "bc", 2);
    char *res2 = unionCharArray("a", 1, "bc", 2);
    charArrayEqual(res2, "abc", 3);
    free(res2);

    setTestFunctionParameters("%s %d %s %d", "", 0, "bc", 2);
    char *res3 = unionCharArray("", 0, "bc", 2);
    charArrayEqual(res3, "bc", 2);
    free(res3);
}
