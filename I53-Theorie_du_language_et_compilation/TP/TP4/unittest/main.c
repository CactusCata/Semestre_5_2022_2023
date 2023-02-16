#include "main.h"

int main(int argc, char *argv[]) {

    AFN A = afn_finit("../data/afn1.afn");
    afn_toPng(A, "test3");

    AFD B = afn_determiniser(A);
    afd_toPng(B, "test");
    afd_print(B);

    afd_free(B);


    afn_free(A);
    /*    

    AFD C = afd_finit("../data/afd1.afd");
    afd_toPng(C, "test2");
    afd_free(C);
    */

    /*
    AFN A;
    afn_char(&A, 'a');
    afn_toPng(A, "test4");


    AFN B;
    afn_char(&B, 'w');
    afn_toPng(B, "test5");

    

    AFN C;
    afn_union(&C, A, B);
    afn_toPng(C, "test6");

    AFN D;
    afn_union(&D, C, A);
    afn_toPng(D, "test7");



    AFN E;
    afn_concat(&E, A, B);
    afn_toPng(E, "test8");


    AFN F;
    afn_union(&F, D, E);
    afn_toPng(F, "test9");

    AFN G;
    afn_concat(&G, D, E);
    afn_toPng(G, "test10");

    AFN H;
    afn_kleene(&H, C);
    afn_toPng(H, "test11");

    afn_free(H);
    afn_free(F);
    afn_free(G);

    afn_free(E);
    afn_free(A);
    afn_free(B);
    afn_free(C);
    afn_free(D);
    

   char re[] = "(a+b)c*";
   char txt[] = "ad";
   printf("RE: %s\n", re);
   printf("txt: %s\n", txt);
   AFN Y = buildAFNFromRE(re);
   afn_toPng(Y, "res");
   AFD Z = afn_determiniser(Y);
   afd_toPng(Z, "resdeter");
   if (afn_simuler(Y, txt)) {
    printf("Chaine acceptée\n");
   } else {
    printf("Chaine non-acceptée\n");
   }

    afd_free(Z);
   afn_free(Y);
   */

    /*
    initUnitTest();

    callAllTest_utils();
    callAllTest_arrayUtils();
    callAllTest_vect();

    endUnitTest();
    */

    return 0;

}
