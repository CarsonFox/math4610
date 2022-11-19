#ifndef ROOTFINDING_H
#define ROOTFINDING_H

double functional_iter(double (*f)(double), double x0, int max, double tol);
double newton(double (*f)(double), double x0, int max, double tol);
double bisect(double (*f)(double), double a, double b, double tol);
double secant(double (*f)(double), double a, double b, int max, double tol);

double hybrid_bn(double (*f)(double), double a, double b,
    double threshold, int max, double tol);

double hybrid_bs(double (*f)(double), double a, double b,
    double threshold, int max, double tol);

#endif /* include guard */
