#ifndef  MY_INTEGRALS
#define MY_INTEGRALS

#define TRUE    1
#define FALSE   0

#include <iostream>

int RectangularRule (double (*)(double), double, double, int, double&);
int TrapezoidalRule (double (*)(double), double, double, int, double&);
int SimpsonRule (double (*)(double), double, double, int, double&);
int GaussRule (double (*)(double), double, double, int, int, double&);


// UTILITIES
int sort(double&, double&);

#endif // ! MY_INTEGRALS
