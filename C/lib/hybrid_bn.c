double newton(double (*f)(double), double x0, int max, double tol);
double bisect(double (*f)(double), double a, double b, double tol);

double hybrid_bn(double (*f)(double), double a, double b,
    double threshold, int max, double tol) {
  double bisection_approx = bisect(f, a, b, threshold);
  return newton(f, bisection_approx, max, tol);
}
