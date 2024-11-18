// my_derivatives.cpp
#include "my_derivatives.h"

double FDerivative (double f0, double f1, double h) {
  return (f1 - f0) / h;
}

double BDerivative (double f0, double f_1, double h) {
  return (f0 - f_1) / h; // _ stands for -
}

double CDerivative (double f_1, double f1, double h) {
  return (f1 - f_1)*.5 / h;
}

double HDerivative (double f_2, double f_1, double f1, double f2, double h) {
  return (f_2 - 8*f_1 + 8*f1 - f2) / (12*h);
}

double SecondDerivative (double f0, double f_1, double f1, double h) {
  return (f1 - 2*f0 + f_1) / (h*h);
}
