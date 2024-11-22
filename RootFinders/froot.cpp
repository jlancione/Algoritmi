#include <iostream>
#include <cmath>
#include <iomanip>
#include "my_rootfinders.h"

#define TEST    1

double Func (double);
double deFunc (double);

int main() {
  using namespace std;

  double a, b;
  #if TEST == 1
    a = -1.;
    b = 1.;

// to test convergence out of original boundary (for newton and secant)
//  a = .2;  
//  b = .4;
  #endif
  #if TEST == 2
    a = -5.;
    b = 0.;
  #endif
  #if TEST == 3
    a = 0.;
    b = 2.;
  #endif


  double tol = 1.e-7;
  double zbis, zfpos, zsec, znewt;
  int kbis, kfpos, ksec, knewt;

  Bisection(Func, a, b, tol, tol, zbis, kbis);
  FalsePos(Func, a, b, tol, tol, zfpos, kfpos);
  Secant(Func, a, b, tol, tol, zsec, ksec);
  Newton(Func, deFunc, a, b, tol, tol, znewt, knewt);


  cout << "Bisezione: iterations = " << kbis << "; zero = " << zbis << endl;
  cout << "FalsePos: iterations = " << kfpos << "; zero = " << zfpos << endl;
  cout << "Secant: iterations = " << ksec << "; zero = " << zsec << endl;
  cout << "Newton: iterations = " << knewt << "; zero = " << znewt << endl;
  return 0;
}


double Func (double x) {
  #if TEST == 1
    return exp(-x) - x;
  #endif
  #if TEST == 2
    return 5. + x*( 1. + x*( -3. + x)); // hornet's method
  #endif
  #if TEST == 3
    return exp( 1./ ( x + .5)) - ( 3 + 2*x) / ( 1 +x);
  #endif
}
double deFunc (double x) {
  #if TEST == 1
    return -exp(-x) -1;
  #endif
  #if TEST == 2
    return  1. + x*( -6. + 3*x); // hornet's method
  #endif
  #if TEST == 3
    return 1./((1+x) * (1+x)) - 1./((x + .5)*(x+ .5)) * exp(1./ (x+.5));
  #endif
}
