#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
        printf("%f", x.data[i]);
        if (i < x.length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
