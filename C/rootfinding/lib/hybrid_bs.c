#include <math.h>

double secant(double (*f)(double), double a, double b, int max, double tol);

double hybrid_bs(double (*f)(double), double a, double b,
    double threshold, int max, double tol) {
  int k = ((int) -log2(threshold / (b-a))) + 1;

  for (int i = 0; i < k; i++) {
    double midpoint = (a + b) / 2;
    double fa = f(a), fm = f(midpoint), fb = f(b);

    if (fa * fm < 0)
      b = midpoint;
    else if (fm * fb < 0)
      a = midpoint;
    else
      return NAN;
  }

  return secant(f, a, b, max, tol);
}
