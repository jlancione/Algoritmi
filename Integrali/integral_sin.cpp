#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>

double TrapezoidalRule (double (*F)(double), double a, double b, int N);
double SimpsonRule (double (*F)(double), double a, double b, int N);
double GaussRule (double (*F)(double), double a, double b, int N, int Ng);

double Si(double x);


int main() {
  using namespace std;
  cout << setiosflags(ios::scientific);

  // ci va 1 if per evitare la singolarità in 0, nn si può evitare
  double trap_sum, simps_sum, gauss_sum;
  int i;    // loop index
  int Ng = 3;

  /*
  int n;
  n = 1; // initialization for gauss sum
  gauss_sum = GaussRule(Si, 0, 8, n, Ng);
  cout << setw(10) << "[Gaussian n = " << 1 << ", n_g = " << Ng << "] = " << setw(14) << setprecision(10) << gauss_sum << endl;

  for (n = 1; n < 9; n *= 2) {
    trap_sum = TrapezoidalRule(Si, 0, 8, n);
    cout << setw(23) << "[Trapezoidal, n = " << n << "] = " << setw(14) << setprecision(10) << trap_sum << endl;
  }

  for (n = 1; n < 9; n *= 2) {
    simps_sum = SimpsonRule(Si, 0, 8, n);
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

  double sum, x0;
  double x1 = a;

  sum = 0.0;
  for(i = 0; i < N; i++) {
    x0 = x1;
    x1 = a + i*dx;
    sum += GaussRule(Si, x0, x1, 1, Ng);
    fdata << x0 + dx / 2 << "  " << sum << endl;
  }

  fdata.close();

  return 0;
}



double TrapezoidalRule (double (*F)(double), double a, double b, int N){ // N è il numero di intervalli
  double h = ( b - a)/(double)N;
  double sum = 0;

  sum += ( F(a) + F(b)) / (double) 2;
  for(int i=1; i < N; i++){
   sum += F(a + h*i); 
  }
  sum *= h;
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

double Si(double x) {
  if (x < 1.e-3) { return 1.0 - x*x / (3.0*2) + x*x*x*x/125.0;}
  else {return sin(x)/ x;}
}

