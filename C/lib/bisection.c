#include <math.h>
#include <stdio.h>

double bisect(double (*f)(double), double a, double b, double tol) {
  int k = ((int) -log2(tol / (b-a))) + 1;

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

  return (a + b) / 2;
}
