#include <stdio.h>
#include <math.h>

#include "rootfinding.h"

int main(void) {
  double f(double x) {
    return x * exp(-x);
  }

  printf("%f\n", functional_iter(f, 1/2, 1000, 1e-6));
  printf("%f\n", newton(f, 1/2, 1000, 1e-6));
  printf("%f\n", bisect(f, -1, 2, 1e-6));
  printf("%f\n", secant(f, -1, 1, 1000, 1e-6));
  printf("%f\n", hybrid_bn(f, -1, 2, 1e-3, 100, 1e-9));
  printf("%f\n", hybrid_bs(f, -1, 2, 1e-3, 100, 1e-9));

  return 0;
}
