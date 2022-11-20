#include <stdio.h>

#include "munit/munit.h"

#include "vector.h"

int main(void) {
    vector x = new_vec(4, 3.0, -4.0, 2.0, 5.0);
    printf("x = ");
    print_vec(x);

    return 0;
}