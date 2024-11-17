#ifndef MY_ODESOLVERS
#define MY_ODESOLVERS

#include <iostream>

#define TRUE    1
#define FALSE   0

void EulerStep (double, double *, void(*)(double, double *, double *),
                double, int);
void RK2Step (double, double *, void(*)(double, double *, double *),
              double, int);
void RK4Step (double, double *, void(*)(double, double *, double *),
              double, int);


#endif // ! MY_ODESOLVERS
