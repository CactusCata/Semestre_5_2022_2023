#include "vect_unit.h"

void callAllTest_vect() {
    createVect_test();
    createVectFromIntArray_test();
    freeVect_test();
    vectIsEmpty_test();
    vectAdd_test();
    vectAddAll_test();
    vectSet_test();
    getBestVectIndex_test();
    vectContrainsValue_test();
    expendVectSize_test();
    sameValuesOccurenciesInVect_test();
    unionVectAsSet_test();
    intersectionOfVectIsNotEmpty_test();
    serializeVect_test();
    serializeRealVect_test();
    printVect_test();
    printVectArray_test();
    serializeVectArray_test();
    vectToIntArray_test();
    intArrayToVect_test();
    vectGet_test();
    vectEqualsToVect_test();
    vectCopy_test();
}

void createVect_test() {
    setTestFunctionName("createVect");

    Vect *vect1 = createVect(false);
    setTestFunctionParameters("");
    int expectedArray[] = {-1};
    intArrayEqual(vect1->array, expectedArray, 1);
    intEqual(vect1->size, 0);
    intEqual(vect1->realSize, 1);
    freeVect(vect1);
}

void createVectFromIntArray_test() {
    setTestFunctionName("createVectFromIntArray");

    int array[] = {1,5,9};
    setTestFunctionParameters("{1,5,9} %d %s", 3, "false");
    Vect *vect = createVectFromIntArray(array, 3, false);
    intArrayEqual(vect->array, array, 3);
    intEqual(vect->size, 3);
    intEqual(vect->realSize, 4);
    freeVect(vect);
}

void freeVect_test() {

}

void vectIsEmpty_test() {
    setTestFunctionName("vectIsEmpty");

    Vect *vect = createVect(false);
    setTestFunctionParameters("");
    boolEqual(vectIsEmpty(vect), true);

    vectAdd(vect, 3);
    setTestFunctionParameters("");
    boolEqual(vectIsEmpty(vect), false);

    freeVect(vect);
}

void vectAdd_test() {
    setTestFunctionName("vectAdd");

    Vect *vect = createVect(false);
    
    setTestFunctionParameters("vect %d", 14);
    vectAdd(vect, 14);
    int expectedArray1[] = {14, -1};
    intArrayEqual(vect->array, expectedArray1, 2);

    setTestFunctionParameters("vect %d", 86);
    vectAdd(vect, 86);
    int expectedArray2[] = {14, 86, -1};
    intArrayEqual(vect->array, expectedArray2, 3);

    freeVect(vect);

    vect = createVect(true);

    setTestFunctionParameters("vect %d", 86);
    vectAdd(vect, 86);
    int expectedArray3[] = {86, -1};
    intArrayEqual(vect->array, expectedArray3, 2);

    setTestFunctionParameters("vect %d", 14);
    vectAdd(vect, 14);
    int expectedArray4[] = {14, 86, -1};
    intArrayEqual(vect->array, expectedArray4, 3);

    freeVect(vect);
}

void vectAddAll_test() {

}

void vectSet_test() {

}

void getBestVectIndex_test() {

}

void vectContrainsValue_test() {

}

void expendVectSize_test() {

}

void sameValuesOccurenciesInVect_test() {

}

void unionVectAsSet_test() {

}

void intersectionOfVectIsNotEmpty_test() {

}

void serializeVect_test() {

}

void serializeRealVect_test() {

}

void printVect_test() {

}

void printVectArray_test() {

}

void serializeVectArray_test() {

}

void vectToIntArray_test() {

}

void intArrayToVect_test() {

}

void vectGet_test() {

}

void vectEqualsToVect_test() {

}

void vectCopy_test() {

}