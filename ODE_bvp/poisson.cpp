#include <iostream>
#include <cmath>
#include <fstream>
#include "my_odesolvers.h"

#define NINT    1000

void RHSide(double r, double *phi, double *R);

int main() {
  using namespace std;
  ofstream fdata;
  fdata.open("poisson.dat");

  // Boundaries
    double a, b;
    a = 0.;
    b = 20.;

  double r, dr, phi[2], s; // s is the shooting variable
  dr = ( b - a ) / NINT;

  int n, j;
  for(n = 0; n <= 5; n++) {
    s = .2*n;
    phi[0] = a;
    phi[1] = s;  // shoot for initial condition

    for(j=0; j < NINT; j++) { 
      r = a + j*dr;
      RK4Step(r, phi, RHSide, dr, 2);

      fdata << r << " " << phi[0] << endl;
    }
    fdata << endl << endl;
  }

  fdata.close();
  return 0;
}


void RHSide(double r, double *phi, double *R) {
  R[0] = phi[1];
  R[1] = -4. * M_PI * r * exp(-r) *M_1_PI*.125;
}
  
