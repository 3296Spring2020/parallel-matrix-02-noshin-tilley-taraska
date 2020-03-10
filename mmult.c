/**
 * An unoptimized implementation of matrix multiplication.
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "mat.h"

/**
 * An unoptimized algorithm for matrix multiplication.
 * 
 * @param c : the matrix in which to place the result of the matrix multiplication.
 * @param a : the first matrix.
 * @param aRows : the number of rows in a.
 * @param aCols : the number of columns in a.
 * @param b : the second matrix.
 * @param bRows : the number of rows in b.
 * @param bCols : the number of columns in b.
 * @return 0 if the matrix multiplication is successful.
 */
//// init
//int mmult(double *c,
//	      double *a, int aRows, int aCols,
//	      double *b, int bRows, int bCols) {
//
//    for(int i = 0; i < aRows; ++i) {
//        for(int j = 0; j < bCols; ++j) {
//            c[i * bCols + j] = 0;
//            for(int k = 0; k < aRows; ++k) {
//                c[i * bCols + j] += a[i * aRows + k] * b[k * bCols + j];
//            }
//        }
//    }
//
//  return 0;
//}
//// copied
//int mmult(double *c,
//          double *a, int aRows, int aCols,
//          double *b, int bRows, int bCols) {
//
//    for (int i = 0; i < aRows; i++) {
//        for (int j = 0; j < bCols; j++)
//            c[i][j] = 0;
//        for (int k = 0; k < aRows; k++)
//            for (int l = 0; l < bCols; l++)
//                c[i][l] += a[i][k] * b[k][l];
//    }
//    return 0;
//}
//// test
// int mmult(double *c,
//           double *a, int aRows, int aCols,
//           double *b, int bRows, int bCols) {

//     for (int i = 0; i < aRows; i++) {
//         int j = 0;
//         for (j = 0; j < bCols; j++)
//             c[i * bCols + j] = 0;
//         for (int k = 0; k < aRows; k++)
//             for (int l = 0; l < bCols; l++)
//                 c[i * bCols + j] += a[i * aRows + k] * b[k * bCols + j];
//     }
//     return 0;
// }
//Test2
// int mmult(double *c,
//           double *a, int aRows, int aCols,
//           double *b, int bRows, int bCols) {
//     int N = aRows;
//     for (int i = 0; i < N; i++) {
//         int j = 0;
//         for (j = 0; j < N; j++)
//             c[i * bCols + j] = 0;
//         for (int k = 0; k < N; k++)
//             for (int l = 0; l < N; l++)
//                 c[i * N + j] += a[i * N + k] * b[k * N + j];
//     }
//     return 0;
// }

////last
int mmult(double *c,
          double *a, int aRows, int aCols,
          double *b, int bRows, int bCols) {
    int i,j,k;
    for (i = 0; i < aRows; i++) {
        for (j = 0; j < bCols; j++) {
            c[i * bCols + j] = 0;
        }
        for (k = 0; k < aCols; k++) {
            for (j = 0; j < bCols; j++) {
                c[i * bCols + j] += a[i * aCols + k] * b[k * bCols + j];
            }
        }
    }
    return 0;
}



