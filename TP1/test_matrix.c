#include "matrix.h"

#include <cblas.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int m = 1000;
  int p = 2000;
  int n = 3000;
  matrix *A = allocate_matrix(m, p);
  matrix *B = allocate_matrix(p, n);
  matrix *C = allocate_matrix(m, n);
  if (A == NULL || B == NULL || C == NULL) {
    return -1;
  }
  double **a = A->a;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      a[i][j] = drand48();
    }
  }
  double **b = B->a;
  for (int i = 0; i < p; i++) {
    for (int j = 0; j < n; j++) {
      b[i][j] = drand48();
    }
  }
  time_t t;
  t = time(NULL);

  if (mult_matrix(A, B, C) != 0) {
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    return -1;
  }
  time_t end;
  end = time(NULL);
  printf("Time taken: %ld seconds\n", end - t);

  double *Adata = &A->a[0][0];
  double *Bdata = &B->a[0][0];
  double *Cdata = &C->a[0][0];
  time_t start_blas;
  start_blas = time(NULL);
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, p, 1.0, Adata, p,
              Bdata, n, 0.0, Cdata, n);

  time_t end_blas;
  end_blas = time(NULL);
  printf("BLAS Time taken: %ld seconds\n", end_blas - start_blas);
  return 0;
}
