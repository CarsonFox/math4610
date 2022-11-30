#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "matrix.h"
#include "vector.h"

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

void free_mat(matrix mat) {
    free(mat.data);
    mat.rows = mat.cols = 0;
    mat.data = NULL;
}

//The following three functions are convenience functions that
//produce matrix/vector views of owned data.
//They should not be freed, and so the resulting
//structs should not leave this file.
vector row_as_vec(matrix A, int row) {
    vector x = {
            .length = A.cols,
            .data = A.data + row * A.cols,
    };
    return x;
}

matrix vec_as_mat(vector x) {
    matrix result = {
            .rows = x.length,
            .cols = 1,
            .data = x.data,
    };
    return result;
}

vector mat_as_vec(matrix A) {
    //Must be a column vector
    assert(A.cols == 1);
    vector result = {
            .length = A.rows,
            .data = A.data,
    };
    return result;
}

void print_mat(matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        print_vec(row_as_vec(mat, i));
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

double row_col_dot(matrix A, matrix B, int row, int col) {
    double sum = 0;

    #pragma omp parallel for
    for (int i = 0; i < A.cols; i++) {
        double prod = mat_at(A, row, i) * mat_at(B, i, col);

        #pragma omp critical
        {
            sum += prod;
        }
    }

    return sum;
}

matrix mat_mul(matrix A, matrix B) {
    assert(A.cols == B.rows);

    matrix result = {
            .rows = A.rows,
            .cols = B.cols,
            .data = calloc(A.rows * B.cols, sizeof(double)),
    };

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            double prod = row_col_dot(A, B, i, j);
            mat_set(result, i, j, prod);
        }
    }

    return result;
}

vector mat_act(matrix A, vector x) {
    matrix B = vec_as_mat(x);
    matrix result = mat_mul(A, B);
    return mat_as_vec(result);
}

matrix mat_hadamard(matrix A, matrix B) {
    check_matrix_sizes(A, B);

    matrix result = {
            .rows = A.rows,
            .cols = A.cols,
            .data = calloc(A.rows * A.cols, sizeof(double)),
    };

    #pragma omp parallel for
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.rows; j++) {
            double sum = mat_at(A, i, j) * mat_at(B, i, j);
            mat_set(result, i, j, sum);
        }
    }

    return result;
}
