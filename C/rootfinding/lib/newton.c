#include <math.h>

double dx(double fxe, double fx, double e) {
  return (fxe - fx) / e;
}

double newton(double (*f)(double), double x0, int max, double tol) {
  double guess = x0, e = 1e-9;

  for (int i = 0; i < max; i++) {
    double error = fabs(f(guess));
    
    if (error < tol)
      return guess;

    double fxe = f(guess + e), fx = f(guess);
    guess = guess - fx / dx(fxe, fx, e);
  }

  return guess;
}

