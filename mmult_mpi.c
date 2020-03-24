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
//     int aRows, aCols, bCols, bRows;
    double *aa;    /* the A matrix */
    double *bb;    /* the B matrix */
    double *cc1;    /* A x B computed using the omp-mpi code you write */
    double *cc2;    /* A x B computed using the conventional algorithm */
    double *buffer;
    double *response;
    int myid, numprocs, i, j, row, numsent, sender, ansType, master;

    double *buff;
    double ans;
    srand(time(0));
    double starttime, endtime;
    MPI_Status status;

    /* insert other global variables here */
    int nrows, ncols;
    int x;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if (argc > 1) {


        for(x = 100; x < 1000;) {


            //FILE* matrixAPtr , *matrixBPtr;
            //matrixAPtr = fopen(argv[1],"r");
            //matrixBPtr = fopen(argv[2],"r");
            //fscanf(matrixAPtr, "rows(%d) cols(%d)", &aRows, &aCols);
            //fscanf(matrixBPtr, "rows(%d) cols(%d)", &bRows, &bCols);
            //if(aCols != bRows || aRows!= bCols){
            //fprintf(stderr, "*******Matrices have different dimensions!*******\n");
            //exit(1);
            // }


            numsent = 0;
            nrows = x;
            ncols = nrows;
            master = 0;
            aa = malloc(sizeof(double) * nrows * ncols);
            bb = malloc(sizeof(double) * nrows * ncols);
            cc1 = malloc(sizeof(double) * nrows * nrows);
            buffer = (double *) malloc(sizeof(double) * ncols);
            response = (double *) malloc(sizeof(double) * nrows);


            if (myid == 0) {
                aa = gen_matrix(nrows, ncols);
                bb = gen_matrix(nrows, ncols);
                starttime = MPI_Wtime();
                MPI_Bcast(bb, nrows * ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
                // this is the number of rows we will send, it is the minimum between numprocs - 1 or all the rows nrows
                for (int i = 0; i < min(numprocs - 1, nrows); i++) {
                    // fill up the buffer for this given row
                    for (int j = 0; j < ncols; j++) {
                        buffer[j] = aa[i * ncols + j];
                    }
                    // send the buffer starting at ID 1 (can't send from master to master), and increment numsent to keep track of the # of rows sent
                    MPI_Send(buffer, ncols, MPI_DOUBLE, i + 1, ++numsent, MPI_COMM_WORLD);
                }

                // for i =0 to nrows
                for (int i = 0; i < nrows; i++) {
                    // receive a buffer from the child
                    MPI_Recv(response, nrows, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

                    // determine who sent this buffer (MPI is non-deterministic, any of the child procs could have sent this)
                    sender = status.MPI_SOURCE;

                    // get the index of the row that was sent
                    row = status.MPI_TAG;

                    // fill up the row of cc1 this response corresponds to
                    for (int l = 0; l < ncols; l++) {
                        cc1[row * nrows + l] = response[l];
                    }

                    // if we didnt send all the rows (i.e there were more rows than procs)
                    if (numsent < nrows) {
                        // fill up a buffer using the next row of aa
                        for (int l = 0; l < nrows; l++) {
                            buffer[l] = aa[numsent * nrows + l];
                        }
                        // send it to a child
                        MPI_Send(buffer, ncols, MPI_DOUBLE, sender, ++numsent, MPI_COMM_WORLD);
                    } else {
                        // we are done, signal that we are complete by sending a 0 tag
                        MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
                    }

                }
                endtime = MPI_Wtime();
                printf("%f\n", (endtime - starttime));
                printf("%d", x);
                double fintime = endtime - starttime;
                FILE *file;
                file = fopen("data.txt", "a");
                fprintf(file, "%lf ", fintime);
                fclose(file);
                free(response);
                free(buffer);
                free(cc1);
                free(bb);
                free(aa);
                
                x = x+100;


            }
// this is a child process
            else {
                // exit if there were more processes than rows...
                MPI_Bcast(bb, nrows * ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
                if (myid <= nrows) {
                    // run indefinitely
                    while (1) {
                        // receive a row from the master
                        MPI_Recv(buffer, ncols, MPI_DOUBLE, master, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                        // if the tag sent is 0, break
                        if (status.MPI_TAG == 0) {
                            break;
                        }
                        // get the id of the row we sent (remember we sent it to proc + 1, so the row is tag - 1
                        row = status.MPI_TAG - 1;

                        // multiply the vector times the matrix and place it in response
                        mmult(response, buffer, 1, ncols, bb, nrows, ncols);
                        // send this response back to master with the approriate row tag
                        MPI_Send(response, nrows, MPI_DOUBLE, master, row, MPI_COMM_WORLD);
                    }
                }
            }
            double fintime = endtime - starttime;
            FILE *file;
            file = fopen("data.txt", "a");
            fprintf(file, "%lf ", fintime);
            fclose(file);
            free(response);
            free(buffer);
            free(cc1);
            free(bb);
            free(aa);
        }
    } else {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}
