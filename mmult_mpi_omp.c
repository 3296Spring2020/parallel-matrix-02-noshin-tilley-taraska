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

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);



int main(int argc, char* argv[]) {
    int aRows, aCols, bCols, bRows;
    double *aa;    /* the A matrix */
    double *bb;    /* the B matrix */
    double *cc1;    /* A x B computed using the omp-mpi code you write */
    double *cc2;    /* A x B computed using the conventional algorithm */
    int myid, numprocs, i, j, row, sent, sentFrom, ansType;
    double *buff;
    double ans;
    srand(time(0));
    double starttime, endtime;
    MPI_Status status;

    /* insert other global variables here */

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1) {
        
        
        //FILE* matrixAPtr , *matrixBPtr;
        //matrixAPtr = fopen(argv[1],"r");
        //matrixBPtr = fopen(argv[2],"r");
        //fscanf(matrixAPtr, "rows(%d) cols(%d)", &aRows, &aCols);
        //fscanf(matrixBPtr, "rows(%d) cols(%d)", &bRows, &bCols);
        //if(aCols != bRows || aRows!= bCols){
            //fprintf(stderr, "*******Matrices have different dimensions!*******\n");
            //exit(1);
       // }
        
        
        
        bCols = atoi(argv[1]);
        aRows = atoi(argv[1]);
        bRows = aRows + 2;
        aCols = aRows + 2;


        if (myid == 0) {
            // Master Code goes here
            //aa = gen_matrix(nrows, ncols);
            aa = malloc(sizeof(double) * aRows * aCols);
            //bb = gen_matrix(ncols, nrows);
            bb = malloc(sizeof(double) * bRows * bCols);

            for (i = 0; i < aRows; i++) {
                for (j = 0; j < aCols; j++) {
                    aa[i * aCols + j] = (double) rand() / RAND_MAX;
                }
            }
            for (i = 0; i < bRows; i++) {
                for (j = 0; j < bCols; j++) {
                    bb[i * bCols + j] = (double) rand() / RAND_MAX;
                }
            }
            cc1 = (double *) malloc(sizeof(double) * aRows * bCols);
            starttime = MPI_Wtime();
            sent = 0;

            MPI_Bcast(bb, (bRows * bCols), MPI_DOUBLE, 0, MPI_COMM_WORLD);
            //
            buff = (double *) malloc(sizeof(double) * aCols);
            for (i = 0; i < min(numprocs - 1, aRows); i++) {
                for (j = 0; j < aCols; j++) {
                    buff[j] = aa[i * aCols + j];
                }
                MPI_Send(buffer, aCols, MPI_DOUBLE, i + 1, i + 1, MPI_COMM_WORLD);
                sent++;
            }
            for (i = 0; i < aRows; i++) {
                MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                sender = status.MPI_SOURCE;
                ansType = status.MPI_TAG;
                cc1[ansType - 1] = ans;

                if (sent < aRows) {
                    for (j = 0; j < aCols; j++) {
                        buff[j] = aa[sent * aCols + j];
                    }
                    MPI_Send(buffer, aCols, MPI_DOUBLE, sentFrom, sent + 1, MPI_COMM_WORLD);
                    sent++;
                } else {
                    MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sentFrom, 0, MPI_COMM_WORLD);
                }



                /* Insert your master code here to store the product into cc1 */
                endtime = MPI_Wtime();
                printf("%f\n", (endtime - starttime));
                cc2 = (double *) malloc(sizeof(double) * aRows * bCols);
                mmult(cc2, aa, aRows, aCols, bb, bCols, bRows);
                compare_matrices(cc2, cc1, aRows, bCols);
            }
            } else {
                // Slave Code goes here
                MPI_Bcast(bb, (bRows*bCols), MPI_DOUBLE, 0, MPI_COMM_WORLD);
                if(myid <= aRows){
                    while(1){
                        MPI_Recv(buffer,aCols,MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                        if(status.MPI_TAG == 0){
                            break;
                        }
                        row=status.MPI_TAG;
                        ans = 0.0;
                        for(j=0;j<aCols;j++){
                            ans+=buff[j] * bb[j*bCols+row];
                        }
                        MPI_Send(&ans, 1 , MPI_DOUBLE, 0, row, MPI_COMM_WORLD);
                    }

            }
            }
        } else {
            fprintf(stderr, "Usage matrix_times_vector <size>\n");
        }
        MPI_Finalize();
        return 0;
    }
