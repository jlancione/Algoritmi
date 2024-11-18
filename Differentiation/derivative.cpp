#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "my_derivatives.h"

int main() {
  using namespace std;
  ofstream fdata;
  fdata.open("derivative.dat");

  double f_2, f_1, f0, f1, f2, h; // _ stands for -
  double df0, df;
  double err;

  f0 = sin(1.);
  df0 = cos(1.);

  int counter = 0;
  for (h=.5; counter < 10; h*=.5) {
    f_2 = sin(1. - 2*h);
    f_1 = sin(1. - h);
    f1 = sin(1. + h);
    f2 = sin(1. + 2*h);

    fdata << 1./h << " ";
    df = FDerivative(f0, f1, h);
    err = abs(df0 - df);
    fdata << err << " "; 

    df = BDerivative(f0, f_1, h);
    err = abs(df0 - df);
    fdata << err << " "; 

    df = CDerivative(f_1, f1, h);
    err = abs(df0 - df);
    fdata << err << " "; 

    df = HDerivative(f_2, f_1, f1, f2, h);
    err = abs(df0 - df);
    fdata << err << " "; 
    fdata << endl;

    counter++;
  }
  fdata.close();
  return 0;
}
