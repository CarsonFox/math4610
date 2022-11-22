#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"

matrix new_matrix(int m, int n, ...) {
    va_list argp;
    va_start(argp, n);

    matrix x = {
            .rows = m,
            .cols = n,
            .data = calloc(m * n, sizeof(double)),
    };

    for (int i = 0; i < m * n; i++) {
        x.data[i] = va_arg(argp, double);
    }

    va_end(argp);
    return x;
}

void free_mat(matrix A) {
    free(A.data);
    A.rows = A.cols = 0;
    A.data = NULL;
}

//Not really the best idea, so not part of the public interface.
//This is because the memory isn't owned by the struct, so shouldn't
//be freed. No vector made this way should leave this file.
vector row_as_vec(matrix A, int row) {
    vector x = {
            .length = A.cols,
            .data = A.data + row * A.cols,
    };
    return x;
}

void print_mat(matrix A) {
    for (int i = 0; i < A.rows; i++) {
        print_vec(row_as_vec(A, i));
    }
}

void check_matrix_sizes(matrix A, matrix B) {
    assert(A.cols == B.cols);
    assert(A.rows == B.rows);
}

double mat_at(matrix A, int i, int j) {
    return A.data[i * A.cols + j];
}

void mat_set(matrix A, int i, int j, double val) {
    A.data[i * A.cols + j] = val;
}

matrix mat_add(matrix A, matrix B) {
    check_matrix_sizes(A, B);

    matrix result = {
            .rows = A.rows,
            .cols = A.cols,
            .data = calloc(A.rows * A.cols, sizeof(double)),
    };

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.rows; j++) {
            double sum = mat_at(A, i, j) + mat_at(B, i, j);
            mat_set(result, i, j, sum);
        }
    }

    return result;
}

matrix mat_sub(matrix A, matrix B) {
    check_matrix_sizes(A, B);

    matrix result = {
            .rows = A.rows,
            .cols = A.cols,
            .data = calloc(A.rows * A.cols, sizeof(double)),
    };

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.rows; j++) {
            double sum = mat_at(A, i, j) - mat_at(B, i, j);
            mat_set(result, i, j, sum);
        }
    }

    return result;
}

matrix mat_mul(matrix A, matrix B) {

}

vector mat_act(matrix A, vector x) {

}
