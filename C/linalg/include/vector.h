#ifndef LINALG_VECTOR_H
#define LINALG_VECTOR_H

typedef struct vector {
    int length;
    double *data;
} vector;

vector new_vec(int length, ...);
vector vec_zeros(int length);
vector vec_ones(int length);

void print_vec(vector x);

vector vec_add(vector u, vector v);
vector vec_sub(vector u, vector v);
double vec_dot(vector u, vector v);
vector vec_mul(vector u, double c);
vector vec_cross(vector u, vector v);

double vec_norm(vector x, int order);
double vec_max(vector x);

void free_vec(vector u);

#endif
