#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mat.h"

#define MAT_SIZE 5

int test_unoptimized(double *a, int arows, int acols,
                     double *b, int brows, int bcols,
                     double *c_actual) {
    double *c_calc = malloc(MAT_SIZE * MAT_SIZE * sizeof(double));

    mmult(c_calc, a, MAT_SIZE, MAT_SIZE, b, MAT_SIZE, MAT_SIZE);

    int are_same = compare_matrices(c_actual, c_calc, MAT_SIZE, MAT_SIZE);

    free(c_calc);

    return are_same;
}

int make_graphs(){
    for (int size = 1; size < 10; size++){
        clock_t start, end, fin_time1, fin_time2;
//    malloc(MAT_SIZE * MAT_SIZE * sizeof(double));
//    malloc(MAT_SIZE * MAT_SIZE * sizeof(double));
        double* new_mat1 = malloc(size * size * sizeof(double));
        double* new_mat2 = malloc(size * size * sizeof(double));
        double* m1a = gen_matrix(size,size); // needs malloc
        double* m1b = gen_matrix(size,size); // needs malloc
        start = clock();
        mmult1(new_mat1 ,m1a,size,size,m1b,size,size);
        end = clock();
        fin_time1 = (end - start);
        printf("time1: ");
        printf("%lu\n",fin_time1);
        start = clock();
        mmult2(new_mat2 ,m1a,size,size,m1b,size,size);
        end = clock();
        fin_time2 = (end - start);
        printf("time2: ");
        printf("%lu\n",fin_time2);
        free(new_mat1);
        free(new_mat2);

    }
    return 0;

}

int main(void) {
    double *a = read_matrix_from_file("a.txt");
    double *b = read_matrix_from_file("b.txt");
    double *c_actual = read_matrix_from_file("c.txt");
    double *c_calc = malloc(MAT_SIZE * MAT_SIZE * sizeof(double));

    if(!test_unoptimized(a, MAT_SIZE, MAT_SIZE, b, MAT_SIZE, MAT_SIZE, c_actual)) {
        exit(1);
    }

    puts("All tests pass.");


    free(a);
    free(b);
    free(c_actual);
    free(c_calc);

    make_graphs();
}
