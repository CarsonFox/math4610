% Tasksheet 7
% Carson Fox - A02251670
% Dec 3, 2022

# 1. Matrix product

Recall that we can define matrices in C as a struct with 2 dimensions, and a heap-allocated array of contiguous data:

~~~ { .c }
typedef struct matrix {
    int rows, cols;
    double *data;
} matrix;
~~~

The rows are stored in contiguous memory for simplicity. Therefore we provide functions to access the backing data with a pair of indices:

~~~ { .c }
double mat_at(matrix A, int i, int j) {
    return A.data[i * A.cols + j];
}

void mat_set(matrix A, int i, int j, double val) {
    A.data[i * A.cols + j] = val;
}
~~~

Then we can define matrix multiplication, in terms of row/column dot products. Here each  dot product is parallelized.

~~~ { .c }
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
~~~

# 2. Vector Hadamard product

Vectors are defined in the same way as matrices, but with just one dimension.
The Hadamard product can then be defined, as the simple element-wise product of two vectors:

~~~ { .c }
typedef struct vector {
    int length;
    double *data;
} vector;

vector vec_hadamard(vector u, vector v) {
    check_vector_sizes(u, v);

    vector x = {
            .length = u.length,
            .data = calloc(u.length, sizeof(double)),
    };

    #pragma omp parallel for
    for (int i = 0; i < u.length; i++) {
        x.data[i] = u.data[i] * v.data[i];
    }

    return x;
}
~~~

# 3. Parallel Hadamard product

The implementation above computes each individual product in parallel. For large vectors, it might be more efficient to break the vector into pieces and then sum the pieces in the end.

# 4. Matrix Hadamard product

Because matrices here have been defined similar to vectors, the process of computing the Hadamard product is largely the same:

~~~ { .c }
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
~~~

# 5. Outer products

The outer product between two vectors u, v of lengths n, m is an n x m matrix A, where A[i, j] = u[i] * v[j]. A parallel implementation of this follows:

~~~ { .c }
matrix vec_outer_prod(vector u, vector v) {
    matrix A = {
            .rows = u.length,
            .cols = v.length,
            .data = calloc(u.length * v.length, sizeof(double)),
    };

    #pragma omp parallel for
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            mat_set(A, i, j, u.data[i] * v.data[j]);
        }
    }

    return A;
}
~~~
This could be generalized to matrices, but this would require defining tensors of arbitrary dimensions.
