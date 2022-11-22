#include <stdio.h>

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

int main(void) {
    {
        vector x = new_vec(3, 3.0, -4.0, 2.0);
        vector y = new_vec(3, 9.0, 1.0, -7.0);

        test_add(x, y);
        test_sub(x, y);
        test_mul(x, munit_rand_double());
        test_cross_dot(x, y);

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

        free_mat(A);
    }

    return 0;
}