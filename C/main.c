#include "stdio.h"

#include "rootfinding.h"

int main(void) {
  double f(double x) {
    return x - 4;
  }

  printf("%f\n", newton(f, 2, 100, 1e-6));

  return 0;
}
