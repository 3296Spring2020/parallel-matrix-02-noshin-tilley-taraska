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
    double graph_sizes[10];
    double graph_times_unopt[10];
    double graph_times_opt[10];
//     double graph_times_mpi_omp[10];

    int index = 0;
    int n = 100;
    for (int size = n; size < n + 1000; size += 100){
        graph_sizes[index] = size;

        clock_t start, end;
        double fin_time1, fin_time2 //,fin_time3;

//    malloc(MAT_SIZE * MAT_SIZE * sizeof(double));
//    malloc(MAT_SIZE * MAT_SIZE * sizeof(double));
        double* new_mat1 = malloc(size * size * sizeof(double));
        double* new_mat2 = malloc(size * size * sizeof(double));
//         double* new_mat3 = malloc(size * size * sizeof(double));
        double* m1a = gen_matrix(size,size); // needs malloc
        double* m1b = gen_matrix(size,size); // needs malloc
        start = clock();
        mmult1(new_mat1 ,m1a,size,size,m1b,size,size);
        end = clock();
        fin_time1 = ((double) (end - start)) / CLOCKS_PER_SEC;;
        printf("time1: ");
        printf("%f\n",fin_time1);
        start = clock();
        mmult2(new_mat2 ,m1a,size,size,m1b,size,size);
        end = clock();
        fin_time2 = ((double) (end - start)) / CLOCKS_PER_SEC;;
        printf("time2: ");
        printf("%f\n",fin_time2);
//         mmult_mpi_omp(new_mat3 ,m1a,size,size,m1b,size,size);
//         start = clock();
//         end = clock();

//         fin_time3 = ((double) (end - start)) / CLOCKS_PER_SEC;;
//         printf("time3: ");
//         printf("%f\n",fin_time3);



        // used to make graphs
        graph_sizes[index] = size;
        graph_times_unopt[index] = fin_time1;
        graph_times_opt[index] = fin_time2;
//         graph_times_mpi_omp[index] = fin_time3;
        //
        index++;

        free(new_mat1);
        free(new_mat2);
//         free(new_mat3);

    }

    writeArrayToFile("data.txt", graph_sizes, 10);
    writeArrayToFile("data.txt", graph_times_unopt, 10);
    writeArrayToFile("data.txt", graph_times_opt, 10);
//     writeArrayToFile("data.txt", graph_times_mpi_omp, 10);

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
