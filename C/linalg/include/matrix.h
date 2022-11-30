#ifndef LINALG_MATRIX_H
#define LINALG_MATRIX_H

#include "vector.h"

typedef struct matrix {
    int rows, cols;
    double *data;
} matrix;

matrix new_matrix(int m, int n, ...);
void free_mat(matrix mat);

void print_mat(matrix mat);

double mat_at(matrix A, int i, int j);

matrix mat_add(matrix A, matrix B);
matrix mat_sub(matrix A, matrix B);
matrix mat_mul(matrix A, matrix B);
vector mat_act(matrix A, vector x);
matrix mat_hadamard(matrix A, matrix B);

#endif
