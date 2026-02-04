#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

matrix *allocate_matrix(int m, int n) {
  matrix *mat = (matrix *)malloc(sizeof(matrix));
  mat->m = m;
  mat->n = n;
  mat->a = (double **)malloc(m * sizeof(double));
  if (mat->a == NULL)
    return NULL;
  mat->data = (double *)malloc(m * n * sizeof(double));
  if (mat->data == NULL)
    return NULL;
  for (int i = 0; i < m; i++)
    mat->a[i] = mat->data + i * n;
  return mat;
}
void free_matrix(matrix *mat) {
  if (mat == NULL)
    return;
  free(mat->a);
  free(mat->data);
}

int mult_matrix(matrix *A, matrix *B, matrix *C) {
  if (A->n != B->m || A->m != C->m || B->n != C->n) {
    printf("Dimension mismatch: A(%d,%d), B(%d,%d), C(%d,%d)\n", A->m, A->n,
           B->m, B->n, C->m, C->n);
    return -1; // Dimension mismatch
  }
  for (int i = 0; i < A->m; i++) {
    for (int j = 0; j < B->n; j++) {
      C->a[i][j] = 0.0;
      int sum = 0;
      for (int k = 0; k < A->n; k++) {
        sum += A->a[i][k] * B->a[k][j];
      }
      C->a[i][j] = sum;
    }
  }
  return 0; // Success
}
