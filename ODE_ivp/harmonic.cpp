#include <iostream>
#include <cmath>
#include <fstream>
#include "my_odesolvers.h"

#define OMEGA    1

void Acceleration (double*, double *);
void RHS (double, double *, double *);

// ottimo lavoro treno :)
int main() {
  using namespace std;
  ofstream fdata;
  fdata.open("harmonic.dat");

  double period, t, h, energy;

  period = 2*M_PI / OMEGA;
  h = .02 * period;

  double Y[2];
  Y[0] = 1.;
  Y[1] = 0.;

  double *x = Y; 
  double *v = Y + 1;

  // Initial conditions
  *x = 1.;
  *v = 0.;

  int i;
  for(i = 0; i < 500; i++) { // we let the system evolve for 10 periods
    t = i*h;
    PosVerletStep(x, v, Acceleration, h, 1);
    energy = .5*(Y[0]*Y[0] + Y[1]*Y[1]);
    fdata << t << " " << energy << endl;
  }
  fdata << endl << endl;

  // Initial conditions
  *x = 1.;
  *v = 0.;

  for(i = 0; i < 500; i++) { // we let the system evolve for 10 periods
    t = i*h;
    RK2Step(t, Y, RHS, h, 2);
    energy = .5*(Y[0]*Y[0] + Y[1]*Y[1]);
    fdata << t << " " << energy << endl;
  }

  fdata.close();
  return 0;
}


// This is problem specific, here we define the system
void Acceleration (double* x, double *acc) {
  double omega = OMEGA;
  acc[0] = -omega * omega * x[0];  
}

void RHS (double t, double* Y, double* R) {
  R[0] = Y[1];
  R[1] = - OMEGA*OMEGA * Y[0];
}

  
