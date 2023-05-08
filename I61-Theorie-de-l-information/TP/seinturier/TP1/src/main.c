#include "main.h"

int main(int argc, char *argv[]) {
    
    uint n = 10;

    uint num_1 = 24;
    Vec v_1 = int_to_vec(num_1, n);
    vec_print(v_1, n);
    printf("value 1 = %d\n", vec_to_int(v_1, n));

    uint num_2 = 47;
    Vec v_2 = int_to_vec(num_2, n);
    vec_print(v_2, n);
    printf("value 2 = %d\n", vec_to_int(v_2, n));

    Vec d = vec_diff(v_1, v_2, n);
    vec_print(d, n);
    vec_free(d);

    vec_free(v_1);
    vec_free(v_2);





    uint k = 4;
    n = 7;
    Matrix generatice_matrix = get_generatice_matrix();
    printf("Matrice génératrice:\n");
    matrix_print(generatice_matrix, k, n);

    Vec *all = vec_possibilities(k);
    printf("Nombres de 0 à %d:\n", (1 << k) - 1);
    matrix_print(all, 1 << k, k);
    
    printf("Encodages:\n");
    for (uint i = 0; i <= (1 << k) - 1; i++) {
        printf("Encoding the vector: ");
        vec_print(all[i], k);
        Vec v = encode(generatice_matrix, all[i], k, n);
        printf("Is: (%d)", vec_to_int(v, n));
        vec_print(v, n);
        vec_free(v);
    }

    printf("Capacité de décodage: %d\n", capacite_decodage(generatice_matrix, n, k));


    Matrix control_matrix = get_control_matrix();
    Matrix control_matrix_t = matrix_transpose(control_matrix, n - k, n);
    printf("Matrice de controle: \n");
    matrix_print(control_matrix_t, n, n - k);

    for (uint i = 0; i < 1 << n; i++) {
        Vec v = int_to_vec(i, n);
        Syndrome s = syndrome(control_matrix_t, v, k, n);
        if (vec_to_int(s, n - k) == 0) {
            printf("Controle du vecteur: (%d)\n", i);
            vec_print(v, n);
            printf("Donne le syndrome: \n");
            vec_print(s, n - k);
        }
        
        vec_free(v);
        vec_free(s);
    }

    Vec *vec_array = matrix_create(7, 7);
    vec_array[1][1] = 1;
    vec_array[1][4] = 1;
    vec_array[1][5] = 1;
    vec_array[1][6] = 1;

    vec_array[2][2] = 1;
    vec_array[2][4] = 1;
    vec_array[2][5] = 1;

    vec_array[3][1] = 1;
    vec_array[3][2] = 1;
    vec_array[3][6] = 1;

    vec_array[4][0] = 1;
    vec_array[4][1] = 1;
    vec_array[4][2] = 1;
    vec_array[4][4] = 1;

    vec_array[5][0] = 1;
    vec_array[5][3] = 1;
    vec_array[5][4] = 1;
    vec_array[5][5] = 1;

    vec_array[6][0] = 1;
    vec_array[6][2] = 1;
    vec_array[6][2] = 1;


    printf("=======================\n");
    for (uint i = 0; i < 7; i++) {
        vec_print(vec_array[i], 7);
        Syndrome s_clean = syndrome(control_matrix_t, vec_array[i], k, n);
        vec_print(s_clean, n - k);
        Vec vec_noise = vec_noised(vec_array[i], 7, i);
        vec_print(vec_noise, 7);
        Syndrome s_noised = syndrome(control_matrix_t, vec_noise, k, n);
        vec_print(s_noised, n - k);
        vec_free(s_clean);
        vec_free(vec_noise);
        vec_free(s_noised);
        printf("=======================\n");
    }

    matrix_free(vec_array, 7);
    matrix_free(control_matrix_t, n);
    matrix_free(control_matrix, n - k);
    matrix_free(all, 1 << k);
    matrix_free(generatice_matrix, k);

    return 0;
}