#include <stdio.h>
#include <math.h>

#include "rootfinding.h"

int main(void) {
  double f(double x) {
    return x * exp(-x);
  }

  printf("%f\n", hybrid_bn(f, -1, 2, 1e-3, 100, 1e-9));

  return 0;
}
