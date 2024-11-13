#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "my_integrals.h"

double Si(double x);


int main() {
  using namespace std;
  cout << setiosflags(ios::scientific);

  double trap_sum, simps_sum, gauss_sum;
  int i;    // loop index
  int Ng = 3;

  /*
  int n;
  n = 1; // initialization for gauss sum
  GaussRule(Si, 0, 8, n, Ng, gauss_sum);
  cout << setw(10) << "[Gaussian n = " << 1 << ", n_g = " << Ng << "] = " << setw(14) << setprecision(10) << gauss_sum << endl;

  for (n = 1; n < 9; n *= 2) {
    TrapezoidalRule(Si, 0, 8, n, trap_sum);
    cout << setw(23) << "[Trapezoidal, n = " << n << "] = " << setw(14) << setprecision(10) << trap_sum << endl;
  }

  for (n = 1; n < 9; n *= 2) {
    SimpsonRule(Si, 0, 8, n, simps_sum);
    cout << setw(23) << "[Simpson, n = " << n << "] = " << setw(14) << setprecision(10) << simps_sum << endl;
  }
  */

  // creating data file for gnuplot using Gauss method
  double a = 0.0;     // start
  double b = 25.0;    // stop
  int N = 250;        // number of intervals
  double dx = (b - a) / N;

  ofstream fdata;
  fdata.open("Si_integral.dat");

  double sum, subsum, x0;
  double x1 = a;

  sum = 0.0;
  for(i = 0; i < N; i++) {
    x0 = x1;
    x1 = a + i*dx;
    GaussRule(Si, x0, x1, 1, Ng, subsum);
    sum += subsum;
    fdata << x0 + dx / 2 << "  " << sum << endl;
  }

  fdata.close();

  return 0;
}


double Si(double x) {
  if (x < 1.e-3) { return 1.0 - x*x / (3.0*2) + x*x*x*x/125.0;}
  else {return sin(x)/ x;}
}

