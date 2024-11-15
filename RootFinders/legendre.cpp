#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "my_rootfinders.h"

double LegPol (double, int);
double LegPol_wrap (double);
double deLegPol (double);

#define NPOL    5

int main () {
  using namespace std;

  // For bracketing
    int zero_counter;
    double xL[NPOL], xR[NPOL];
    int nsearch = NPOL*20 + 3;
   
  double denominator; 
  double w[NPOL];
  double deLeg;

  zero_counter = Bracket(LegPol_wrap, -1., 1., nsearch, xL, xR);
  cout << "number of 0s = " << zero_counter << endl;

  // For root finding 
    double tol = 1.e-6;
    int iter;
    double zero[zero_counter];

  cout << "For n = " << NPOL << ":" << endl;
  for (int i=0; i < zero_counter; i++) {
    Newton(LegPol_wrap, deLegPol, xL[i], xR[i], tol, tol, zero[i], iter);
  
    cout << "Found zero in (" << xL[i] << ", " << xR[i] << ")" << endl;
  
    // Weights computation
      deLeg = deLegPol(zero[i]);
      denominator = (1. - zero[i] * zero[i]) * deLeg * deLeg;
      w[i] = 2. / denominator;
  
    cout << i << ". zero at " << zero[i] << "; weight = " << w[i] << endl;
  }

  // Plotting the pol
//ofstream fdata;
//fdata.open("legpol.dat");
//
//for(double x = -1.; x < 1.; x+= .1){
//  fdata << x << " " << LegPol_wrap(x) << endl;
//}
//fdata.close();

  return 0;
}


double LegPol (double x, int n) {
  double p0, p1, p2;

  // Initialization
    p0 = 1.; // P_0
    p1 = x; // P_1

  for (int i=1; i <= n; i++) {
    if ( i == n) break;

    p2 = (2*i + 1)* x * p1 - i * p0;
    p2 /= (i+1);

    // Update the recursion
      p0 = p1;
      p1 = p2;
  }
  return p1;
}

double LegPol_wrap (double x) {
  return LegPol(x, NPOL);
}

double deLegPol (double x) {
  double p0, p1, dpol;

  p0 = LegPol(x, NPOL-1);
  p1 = LegPol(x, NPOL);
  dpol = x * p1 - p0;
  dpol *= NPOL;
  dpol /= (x*x - 1);

  return dpol;
}
