#include <math.h>

double functional_iter(double (*f)(double), double x0, int max, double tol) {
  double y = x0 + f(x0), x = x0;
  
  for (int i = 0; i < max && fabs(x - y) > tol; i++) {
    x = y;
    y = x + f(x);
  }

  return x;
}

