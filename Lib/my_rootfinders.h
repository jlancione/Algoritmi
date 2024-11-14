#ifndef MY_ROOT_FINDERS
#define MY_ROOT_FINDERS

#include <iostream>
#include <iomanip>

int Bisection (double (*)(double), double, double, double, double&, int&);
int FalsePos (double (*)(double), double, double, double, double &, int &);
int Secant (double (*)(double), double, double, double, double &, int &);
int Newton (double (*)(double), double (*)(double), double, double, double, double &, int &);

// Utilities
int sort(double&, double&);

#endif // ! MY_ROOT_FINDERS
