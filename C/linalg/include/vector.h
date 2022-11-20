#ifndef LINALG_VECTOR_H
#define LINALG_VECTOR_H

typedef struct vector {
    int length;
    double *data;
} vector;

vector new_vec(int length, ...);
void print_vec(vector x);

#endif
