/** 
 * Incomplete program to multiply a matrix times a matrix using both
 * MPI to distribute the computation among nodes and OMP
 * to distribute the computation among threads.
 */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

#include "mat.h"

int main(int argc, char* argv[])
{
    int nrows, ncols;
    double *aa;	/* the A matrix */
    double *bb;	/* the B matrix */
    double *cc1;	/* A x B computed using the omp-mpi code you write */
    double *cc2;	/* A x B computed using the conventional algorithm */
    int myid, numprocs;
    double starttime, endtime;
    MPI_Status status;

    /* insert other global variables here */
    int aRows, bRows, aCols, bCols;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1) {
        FILE* matrixAPtr , *matrixBPtr;
        matrixAPtr = fopen(argv[1],"r");
        matrixBPtr = fopen(argv[2],"r");
        fscanf(matrixAPtr, "rows(%d) cols(%d)", &aRows, &aCols);
        fscanf(matrixBPtr, "rows(%d) cols(%d)", &bRows, &bCols);
      if(aCols != bRows || aRows!= bCols){
      fprintf(stderr, "*******Matrices have different dimensions!*******\n");
      exit(1);
    }
    }
        
        if (myid == 0) {
            // Master Code goes here
            aa = gen_matrix(nrows, ncols);
            bb = gen_matrix(ncols, nrows);
            cc1 = malloc(sizeof(double) * nrows * nrows); 
            starttime = MPI_Wtime();
            /* Insert your master code here to store the product into cc1 */
            endtime = MPI_Wtime();
            printf("%f\n",(endtime - starttime));
            cc2  = malloc(sizeof(double) * nrows * nrows);
            mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
            compare_matrices(cc2, cc1, nrows, nrows);
        } else {
            // Slave Code goes here
        }
    } else {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}
