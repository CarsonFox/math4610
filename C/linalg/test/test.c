#include <stdio.h>

#include <omp.h>

#include "munit/munit.h"
#include "vector.h"
#include "matrix.h"

void test_add(vector x, vector y) {
    vector result = vec_add(x, y);

    munit_assert_int(result.length, ==, x.length);
    munit_assert_int(result.length, ==, y.length);
    munit_assert_not_null(result.data);

    for (int i = 0; i < result.length; i++) {
        double a = result.data[i], b = x.data[i] + y.data[i];
        munit_assert_double_equal(a, b, 6);
    }

    free_vec(result);
}

void test_sub(vector x, vector y) {
    vector result = vec_sub(x, y);

    munit_assert_int(result.length, ==, x.length);
    munit_assert_int(result.length, ==, y.length);
    munit_assert_not_null(result.data);

    for (int i = 0; i < result.length; i++) {
        double a = result.data[i], b = x.data[i] - y.data[i];
        munit_assert_double_equal(a, b, 6);
    }

    free_vec(result);
}

void test_mul(vector x, double c) {
    vector result = vec_mul(x, c);

    munit_assert_int(result.length, ==, x.length);
    munit_assert_not_null(result.data);

    for (int i = 0; i < result.length; i++) {
        double a = result.data[i], b = x.data[i] * c;
        munit_assert_double_equal(a, b, 6);
    }

    free_vec(result);
}

void test_cross_dot(vector x, vector y) {
    vector c = vec_cross(x, y);

    munit_assert_double_equal(vec_dot(x, c), 0, 6);
    munit_assert_double_equal(vec_dot(y, c), 0, 6);

    free_vec(c);
}

void test_vec_hadamard(vector x, vector y) {
    vector result = vec_hadamard(x, y);

    munit_assert_int(result.length, ==, x.length);
    munit_assert_int(result.length, ==, y.length);
    munit_assert_not_null(result.data);

    for (int i = 0; i < result.length; i++) {
        double a = result.data[i], b = x.data[i] * y.data[i];
        munit_assert_double_equal(a, b, 6);
    }

    free_vec(result);
}

void test_mat_hadamard(matrix A, matrix B) {
    matrix result = mat_hadamard(A, B);

    munit_assert_int(result.rows, ==, A.rows);
    munit_assert_int(result.cols, ==, A.cols);
    munit_assert_int(result.rows, ==, B.rows);
    munit_assert_int(result.cols, ==, B.cols);
    munit_assert_not_null(result.data);

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            double a = mat_at(result, i, j);
            double b = mat_at(A, i, j) * mat_at(B, i, j);
            munit_assert_double_equal(a, b, 6);
        }
    }

    free_mat(result);
}

int main(void) {
    {
        vector x = new_vec(3, 3.0, -4.0, 2.0);
        vector y = new_vec(3, 9.0, 1.0, -7.0);

        test_add(x, y);
        test_sub(x, y);
        test_mul(x, munit_rand_double());
        test_cross_dot(x, y);
        test_vec_hadamard(x, y);

        printf("x = ");
        print_vec(x);
        printf("y = ");
        print_vec(y);

        free_vec(x);
        free_vec(y);
    }
    {
        matrix A = new_matrix(3, 3,
                              3.0, 2.0, 8.0,
                              1.0, -5.0, 9.0,
                              4.0, 6.0, 7.0);
        print_mat(A);

        matrix B = mat_add(A, A);
        printf("\n");
        print_mat(B);

        test_mat_hadamard(A, B);

        matrix C = mat_mul(A, A);
        printf("\n");
        print_mat(C);

        vector x = new_vec(3, 3.0, -4.0, 2.0);
        vector y = mat_act(A, x);
        printf("\nAx = \n");
        print_vec(y);

        free_mat(A);
        free_mat(B);
        free_mat(C);
        free_vec(x);
        free_vec(y);
    }

    return 0;
}