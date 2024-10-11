#include <iostream>
#include <cmath>
#include <iomanip>

double GaussRule (double (*F)(double), double a, double b, int N, int Ng);
double SimpsonRule (double (*F)(double), double a, double b, int N);
double func (double x);
double pol (double x);

int main() {
  using namespace std;
  cout << setiosflags(ios::scientific);

  cout << "Integral of sqrt( 1 + t) between 0 and 3: " << endl;
  cout << setw(9) << "Simpson: " << setw(20) << setprecision(12) << SimpsonRule(func, 0, 3, 2) << endl;
  cout << setw(9) << "Gauss: " << setw(20) << setprecision(12) <<  GaussRule(func, 0, 3, 1, 3) << endl;

  cout << endl;
  cout << "Integral of 1 - x + 2x^2 + x^3 / 2 + x^4 / 4 - x^5 / 8" << endl;
  cout << setw(9) << "Exact: " << setw(20) << setprecision(12) << - 66. / 5. << endl;
  cout << setw(9) << "Simpson: " << setw(20) << setprecision(12) << SimpsonRule(pol, -1, 5, 2) << endl;
  cout << setw(9) << "Gauss: " << setw(20) << setprecision(12) <<  GaussRule(pol, -1, 5, 1, 3) << endl;
  return 0;
}


double GaussRule (double (*F)(double), double a, double b, int N, int Ng) {
  /////////////////////////////
  /// a, b are the extremes of the intervals; N is the number of subintervals; Ng is the number of gaussian points per subinterval
  /////////////////////////////

  double w[32]; double t[32];    // both initialized statically, we have a maximum capacity for the function

  if (Ng == 1) {
    t[0] =           0. ; w[0] = 2.;
  }
  else if (Ng == 2) {
    t[0] = sqrt(1. / 3.); w[0] = 1.;
    t[1] = - t[0];        w[1] = w[0];

  }
  else if (Ng == 3) {
    t[0] =           0  ; w[0] = 8. / 9.;
    t[1] = sqrt(3. / 5.); w[1] = 5. / 9.;
    t[2] = - t[1];        w[2] = w[1];
  }
//if (Ng == 1) { // fatti poi 4 5 6 a casa
//  w[0] = ; x[0] = ;
//  w[1] = ; x[1] = ;
//  w[2] = ; x[2] = ;
//  w[3] = ; x[3] = ;
//}
  else {
    std::cout << "! GaussRule NOT defined for ngauss = " << Ng << std::endl;
    exit(1);
  }

  double sum;
  double x;      // evaluation point for f
  double x0;
  double x1 = a; // to inizialize correctly x1 and x0 in the first subinterval
  double xsum;   // for optimization in the loops

  double dx = (double)(b - a) / (double)N;

  sum = 0.0;
  for(int j = 0; j < N; j++) {       // loop over subintervals
    x0 = x1;
    x1 = a + dx * (j + 1);
    xsum = x0 + x1;

    for(int i = 0; i < Ng; i++) {    // Apply gaussian rule
      x = dx * t[i] + xsum;
      x /= 2.;
      sum += F(x) * w[i];
    }
  }

  sum *= ( b - a) / 2.;

  return sum;

}

double SimpsonRule (double (*F)(double), double a, double b, int N){
  // Note: n must be even

  double h = ( b - a) / (double)N;
  double sum = 0;

  double w = 4.0;

  for(int i=1; i < N; i++){                
    sum += F(a + h*i) * w;  
    w = 6.0 - w;
  }

  sum += F(a) + F(b);
  sum *= h;
  sum /= (double) 3;
  return sum;

}

double func (double x) {
  return sqrt( 1 + x);
}

double pol (double x) {
  return 1 - x + 2 * x*x + (x*x)*x / 2. + (x*x)*(x*x) / 4. - (x*x)*(x*x)*x / 8.;
}
