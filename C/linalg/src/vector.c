#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

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
