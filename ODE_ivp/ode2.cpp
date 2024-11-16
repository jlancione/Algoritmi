#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "my_odesolvers.h"

#define NEQ    2

void RHS(double, double *, double *);
void InitialConditions(double *);

int main() {
  using namespace std;

  double Y[NEQ]; 
  double t, dt, tmax, tmin;
  int nsteps;

  ofstream fdata;
  fdata.open("convergence.dat");
  double err;

  tmin = 0.;
  tmax = 3.;

  int n;
  for(nsteps=4; nsteps<=2048; nsteps*=2) {
    dt = (tmax-tmin) / nsteps; 
    cout << "Computing for nsteps = " << nsteps << endl;
    // Euler method
    InitialConditions(Y);
    for (n = 0; n < nsteps; n++) {
      t = n*dt;
      EulerStep(t, Y, RHS, dt, NEQ);
    }
    err = abs(Y[0] - cos(tmax));
    fdata << dt << " " << nsteps << " " << err << " ";

    // RK2
    InitialConditions(Y);
    for (n = 0; n < nsteps; n++) {
      t = n*dt;
      RK2Step(t, Y, RHS, dt, NEQ);
    }
    err = abs(Y[0] - cos(tmax));
    fdata << err << " ";

    // RK4
    InitialConditions(Y);
    for (n = 0; n < nsteps; n++) {
      t = n*dt;
      RK4Step(t, Y, RHS, dt, NEQ);
    }
    err = abs(Y[0] - cos(tmax));
    fdata << err;

    fdata << endl;
  }

  fdata.close();
  return 0;
}


void RHS (double t, double *Y, double *R) {
  R[0] =  Y[1];
  R[1] = -Y[0];
}

void InitialConditions (double *Y) {
  Y[0] = 1.;
  Y[1] = 0.;
}

// Analitical solution
