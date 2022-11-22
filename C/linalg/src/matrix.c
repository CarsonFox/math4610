#include <stdarg.h>
#include <stdlib.h>

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
