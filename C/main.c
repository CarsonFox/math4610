#include <stdio.h>
#include <math.h>

#include "rootfinding.h"

int main(void) {
  double f(double x) {
    return x * exp(-x);
  }

  printf("%f\n", functional_iter(f, 1/2, 10000, 1e-6));

  return 0;
}
