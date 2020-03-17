/**
 * This file compares the time to multiply matrices
 * both unoptimized and with OMP. 
 */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include "mat.h"


int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
int mmult_omp(double *c,double *a, int aRows, int aCols,double *b, int bRows, int bCols);

double* gen_matrix(int n, int m);
// was a void comp_mat earlier
int compare_matrices(double* a, double* b, int nRows, int nCols);

// double delta time was here


int main(int argc, char* argv[]) {
    struct timespec start;
    struct timespec end;
    struct timespec res;
    double *a, *b, *c1, *c2;
    int n;
    double times[2];
    if (argc > 1) {
        n = atoi(argv[1]);
        a = gen_matrix(n, n);
        b = gen_matrix(n, n);
        c1 = malloc(sizeof(double) * n * n);
        c2 = malloc(sizeof(double) * n * n);clock_t t = clock();
    mmult(c1, a, n, n, b, n, n);
    t = clock() - t;
 times[0] = ((double)t)/CLOCKS_PER_SEC;
    printf("%d %f", n, times[0]);
    t = clock();
    mmult_omp(c2, a, n, n, b, n, n);
    t = clock() - t;
    times[1] = ((double)t)/CLOCKS_PER_SEC;
    printf(" %f", times[1]);
    printf("\n");

         printf("%d %f", n, times[0]);
    t = clock();
    mmult_omp(c2, a, n, n, b, n, n);
    t = clock() - t;
    times[1] = ((double)t)/CLOCKS_PER_SEC;
    printf(" %f", times[1]);
    printf("\n");

       
        compare_matrices(c1, c2, n, n);
    } else {
        fprintf(stderr, "Usage %s <n>\n", argv[0]);
    }
}


}
