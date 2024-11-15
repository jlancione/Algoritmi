#ifndef MY_ROOT_FINDERS
#define MY_ROOT_FINDERS

#include <iostream>
#include <iomanip>

#define TRUE     1
#define FALSE    0

#define DEBUG    FALSE
#define MAX_ITERATIONS    128

int Bisection (double (*)(double), double, double, double, double,
               double &, int &);
int FalsePos  (double (*)(double), double, double, double, double,
               double &, int &);
int Secant    (double (*)(double), double, double, double, double,
               double &, int &);
int Newton    (double (*)(double), double (*)(double),
               double, double, double, double, double &, int &);

// Utilities
int sort (double&, double&);
int Bracket (double (*)(double), double, double,
             int, double [], double []);

#endif // ! MY_ROOT_FINDERS
