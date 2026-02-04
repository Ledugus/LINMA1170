#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
  double **a;
  double *data;
  int m, n;
} matrix;

matrix *allocate_matrix(int n, int m);
void free_matrix(matrix *mat);
int mult_matrix(matrix *A, matrix *B, matrix *C);

#endif // MATRIX_H
