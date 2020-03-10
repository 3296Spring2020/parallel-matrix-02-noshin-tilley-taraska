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
    int a_row, a_col, b_col;
    int num_sent, sender;
    

  /* insert other global variables here */
    double *buffer;
    int anstype, current_row;
  // for accumulating the sum
    double *result;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1) {
        nrows = atoi(argv[1]);
        ncols = nrows;
        
        if (myid == 0) {
            // Master Code goes here
            aa = gen_matrix(nrows, ncols);
            bb = gen_matrix(ncols, nrows);
            cc1 = malloc(sizeof(double) * nrows * nrows); 
            starttime = MPI_Wtime();
            /* Insert your master code here to store the product into cc1 */
            cc1 = malloc(sizeof(double) * nrows * ncols);
            starttime = MPI_Wtime();

            // number of rows sent
            num_sent = 0;
            // Insert your master code here to store the product into cc1
            // broadcast the matrix bb to all slaves
            MPI_Bcast(bb, a_col * b_col, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            // sending a row of aa to slaves at a time
            for (int i = 0; i < min(numprocs - 1, nrows); i++) {
                for (int j = 0; j < a_col; j++) {
                    buffer[j] = aa[i * a_col + j];
                }
                MPI_Send(buffer, a_col, MPI_DOUBLE, i + 1, i + 1, MPI_COMM_WORLD);
                num_sent++;
            }

            // data to get back from slaves
            double *received = (double *) malloc(sizeof(double) * ncols);

            for (int i = 0; i < nrows; i++) {
                MPI_Recv(received, ncols, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG,
                         MPI_COMM_WORLD, &status);
                sender = status.MPI_SOURCE;
                anstype = status.MPI_TAG;  // row number from slaves

                // fill cc1 with data from slaves
                for (int j = 0; j < ncols; j++) {
                    cc1[(anstype - 1) * ncols + j] = received[j];
                }

                // if there are still data to send
                if (num_sent < nrows) {
                    for (int j = 0; j < a_col; j++) {
                        buffer[j] = aa[num_sent * a_col + j];
                    }

                    MPI_Send(buffer, a_col, MPI_DOUBLE, sender, num_sent + 1, MPI_COMM_WORLD);
                    num_sent++;
                } else {
                    // send a STOP signal to the slaves
                    MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
                }
            }
            endtime = MPI_Wtime();
            printf("%f\n",(endtime - starttime));
            cc2  = malloc(sizeof(double) * nrows * nrows);
            mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
            compare_matrices(cc2, cc1, nrows, nrows);
        } else {
            bb = (double *) malloc(sizeof(double) * a_col * b_col);
            MPI_Bcast(bb, a_col * b_col, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            // if there are more rows to process
            if (myid <= nrows) {
                // an infinite loop
                while(1) {
                    MPI_Recv(buffer, a_col, MPI_DOUBLE, 0, MPI_ANY_TAG,
                             MPI_COMM_WORLD, &status);
                    if (status.MPI_TAG == 0) {    // STOP signal from master
                        break;
                    }

                    // which row do we get from the master?
                    current_row = status.MPI_TAG;
                    result = (double *) malloc(sizeof(double) * ncols);

                    for (int i = 0; i < ncols; i++) {
                        for (int j = 0; j < a_col; j++) {
                            result[i] += buffer[j] * bb[j * ncols + i];
                        }
                    }

                    MPI_Send(result, ncols, MPI_DOUBLE, 0, current_row, MPI_COMM_WORLD);
                }
            }
        }
    } else {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}
