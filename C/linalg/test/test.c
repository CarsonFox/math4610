#include <stdio.h>

#include "munit/munit.h"
#include "vector.h"

void test_add(vector x, vector y) {
    vector result = vec_add(x, y);

    munit_assert_int(result.length, ==, x.length);
    munit_assert_int(result.length, ==, y.length);
    munit_assert_not_null(result.data);

    for (int i = 0; i < result.length; i++) {
        double a = result.data[i], b = x.data[i] + y.data[i];
        munit_assert_double_equal(a, b, 6);
    }
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
}

void test_mul(vector x, double c) {
    vector result = vec_mul(x, c);

    munit_assert_int(result.length, ==, x.length);
    munit_assert_not_null(result.data);

    for (int i = 0; i < result.length; i++) {
        double a = result.data[i], b = x.data[i] * c;
        munit_assert_double_equal(a, b, 6);
    }
}

int main(void) {
    vector x = new_vec(4, 3.0, -4.0, 2.0, 5.0);
    vector y = new_vec(4, 9.0, 1.0, -7.0, 6.0);

    test_add(x, y);
    test_sub(x, y);
    test_mul(x, munit_rand_double());

    printf("x = ");
    print_vec(x);
    printf("y = ");
    print_vec(y);

    return 0;
}