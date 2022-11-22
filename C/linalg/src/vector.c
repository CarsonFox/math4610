#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>

#include "../include/vector.h"

vector new_vec(int length, ...) {
    va_list argp;
    va_start(argp, length);

    vector x = {
            .length = length,
            .data = calloc(length, sizeof(double)),
    };

    for (int i = 0; i < length; i++) {
        x.data[i] = va_arg(argp, double);
    }

    va_end(argp);
    return x;
}

vector vec_zeros(int length) {
    vector zeros = {
            .length = length,
            .data = calloc(length, sizeof(double))
    };
    return zeros;
}

vector vec_ones(int length) {
    vector ones = {
            .length = length,
            .data = calloc(length, sizeof(double))
    };

    for (int i = 0; i < length; i++) {
        ones.data[i] = 1.0;
    }

    return ones;
}

void print_vec(vector x) {
    printf("[");
    for (int i = 0; i < x.length; i++) {
        printf("%.2f", x.data[i]);
        if (i < x.length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void check_vector_sizes(vector u, vector v) {
    assert(u.length == v.length);
}

vector vec_add(vector u, vector v) {
    check_vector_sizes(u, v);

    vector x = {
            .length = u.length,
            .data = calloc(u.length, sizeof(double)),
    };

    for (int i = 0; i < u.length; i++) {
        x.data[i] = u.data[i] + v.data[i];
    }

    return x;
}

vector vec_sub(vector u, vector v) {
    check_vector_sizes(u, v);

    vector x = {
            .length = u.length,
            .data = calloc(u.length, sizeof(double)),
    };

    for (int i = 0; i < u.length; i++) {
        x.data[i] = u.data[i] - v.data[i];
    }

    return x;
}

double vec_dot(vector u, vector v) {
    check_vector_sizes(u, v);

    double sum = 0.0;

    for (int i = 0; i < u.length; i++) {
        sum += u.data[i] * v.data[i];
    }

    return sum;
}

vector vec_mul(vector u, double c) {
    vector x = {
            .length = u.length,
            .data = calloc(u.length, sizeof(double)),
    };

    for (int i = 0; i < u.length; i++) {
        x.data[i] = u.data[i] * c;
    }

    return x;
}

double vec_norm(vector x, int order) {
    double sum = 0;
    double p = (double) order;

    for (int i = 0; i < x.length; i++) {
        sum += pow(x.data[i], p);
    }

    return pow(sum, 1/p);
}

double vec_max(vector x) {
    assert(x.length > 0);

    double max = x.data[0];

    for (int i = 1; i < x.length; i++) {
        if (x.data[i] > max) {
            max = x.data[i];
        }
    }

    return max;
}

vector vec_cross(vector u, vector v) {
    assert(u.length == 3);
    check_vector_sizes(u, v);

    double x1 = u.data[1]*v.data[2] - u.data[2]*v.data[1];
    double x2 = u.data[2]*v.data[0] - u.data[0]*v.data[2];
    double x3 = u.data[0]*v.data[1] - u.data[1]*v.data[0];

    return new_vec(3, x1, x2, x3);
}

double triple_prod(vector a, vector b, vector c) {
    vector cross = vec_cross(b, c);
    double prod = vec_dot(a, cross);
    free_vec(cross);
    return prod;
}

void free_vec(vector u) {
    free(u.data);
    u.length = 0;
    u.data = NULL;
}
