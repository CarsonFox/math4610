#include <stdio.h>
#include <math.h>

#include "rootfinding.h"

int main(void) {
  double f(double x) {
    return x * exp(-x);
  }

  printf("%f\n", bisect(f, -3, 2, 1e-6));

  return 0;
}
