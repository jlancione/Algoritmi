#include <iostream>
#include <cmath>
#include <iomanip>
#include "my_rootfinders.h"

double Func (double);
double dFunc(double);

int main () {
  using namespace std;

  double a = -10.;
  double b =  10.;
  int N = 10;
  int k = 0;
  double xL[N], xR[N];

  double tol = 1.e-6;
  int iter = 0;

  k = Bracket (Func, a, b, N, xL, xR);
  cout << "Number of zeros = " << k << endl;
  double zero[k];

  for (int i=0; i<k; i++) {
    cout << endl;
    cout << i << ". Found zero in: (" << xL[i] << ", " << xR[i] << ")" << endl;

    Bisection( Func, xL[i], xR[i], tol, tol, zero[i], iter);
    cout << "Bisection: " << endl;
    cout << "Zero at " << zero[i] << "; after iterations = " << iter << endl;

    FalsePos( Func, xL[i], xR[i], tol, tol, zero[i], iter);
    cout << "FalsePos: " << endl;
    cout << "Zero at " << zero[i] << "; after iterations = " << iter << endl;

    Secant( Func, xL[i], xR[i], tol, tol, zero[i], iter);
    cout << "Secant: " << endl;
    cout << "Zero at " << zero[i] << "; after iterations = " << iter << endl;

    Newton( Func, dFunc, xL[i], xR[i], tol, tol, zero[i], iter);
    cout << "Newton: " << endl;
    cout << "Zero at " << zero[i] << "; after iterations = " << iter << endl;

  }
  return 0;
}


double Func (double x) {
  return sin(x) - ( (x/10.)*(x/10.) + x/5. + 1./3. );
}

double dFunc (double x) {
  return cos(x) - (x/5. + 0.2);
}
