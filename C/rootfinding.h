#ifndef ROOTFINDING_H
#define ROOTFINDING_H

double functional_iter(double (*f)(double), double x0, int max, double tol);
double newton(double (*f)(double), double x0, int max, double tol);
double bisect(double (*f)(double), double a, double b, double tol);
double secant(double (*f)(double), double a, double b, double tol);

#endif /* include guard */
