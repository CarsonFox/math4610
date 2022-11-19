#include <math.h>

double secant(double (*f)(double), double x0, double x1, int max, double tol) {
  double zero = x0;

  for (int i = 0; i < max; i++) {
    double err = fabs(f(zero));

    if (err < tol)
      return zero;

    double fx0 = f(x0), fx1 = f(x1);
    zero = x1 - fx1 * (x1 - x0) / (fx1 - fx0);

    x0 = x1;
    x1 = zero;
  }

  return 0;
}
