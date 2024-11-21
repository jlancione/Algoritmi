#include <iostream>
#include <cmath>
#include <fstream>
#include "my_odesolvers.h"
#include "my_rootfinders.h"

#define NINT    1000   // for RK4 integration
#define SESSION    1

void RHSide(double, double *, double *);
double Residual (double);
double AnalitSol(double);

int main() {
  using namespace std;
  ofstream fdata;

  // Boundaries
    double a, b;
    a = 0.;
    b = 20.;

  double phi0 = 0.; // = phi(a), phi(b) = 1.
  double dphi0;

  double r, dr, phi[2], s; // s is the shooting variable
  dr = ( b - a ) / NINT;

  int n, j;
  #if SESSION == 1 
    // in gnuplot> load "shooting_poisson.gp"
    fdata.open("shooting_poisson.dat");
    for(n = 0; n <= 5; n++) {
      s = .2*n;
      phi[0] = phi0;
      phi[1] = s;  // shoot for initial condition

      for(j=0; j < NINT; j++) { 
        r = a + j*dr;
        RK4Step(r, phi, RHSide, dr, 2);

        fdata << r << " " << phi[0] << endl;
      }
      fdata << endl << endl;
    }
  #endif


  #if SESSION == 2
    // in gnuplot> load "residual_poisson.gp" or "sol_poisson.gp"
    fdata.open("poisson.dat"); 
    double res;
    for(n = 0; n <= 50; n++) { // 50 and s = .1*n is thought to reach s = 5 as maximum
      s = .1*n;
      res = Residual(s);
      fdata << s << " " << res << endl;
    }
    fdata << endl << endl;

    int status, iter;
    status = FalsePos(Residual, .1, 1, 1.e-9, 1.e-9, dphi0, iter);
    if (status == 1) {
      cout << "FalsePos did NOT converge" << endl;
    }
    if (status == 0) {
      cout << "FalsePos converged in " << iter << " iterations";
      cout << endl;
      cout << "Initial condition on dphi is " << dphi0 << endl;
    }

    // Write on disk the error with respect to AnalitSol
    phi[0] = a;
    phi[1] = dphi0;

    for(n=0; n < NINT; n++) { 
      r = a + n*dr;
      RK4Step(r, phi, RHSide, dr, 2);

      fdata << r << " " << phi[0] << " " << AnalitSol(r);
      fdata << endl;
    }
  #endif

  fdata.close();
  return 0;
}


void RHSide(double r, double *phi, double *R) {
  R[0] = phi[1];
  R[1] = -4. * M_PI * r * exp(-r) *M_1_PI*.125;
}

double Residual (double s) {
  // Boundaries
    double a, b;
    a = 0.;
    b = 20.;

  double phi0 = 0.;

  double r, dr, phi[2];
  dr = ( b - a ) / NINT;

  phi[0] = phi0;
  phi[1] = s;

  int j;
  for(j=0; j < NINT; j++) { 
    r = a + j*dr;
    RK4Step(r, phi, RHSide, dr, 2);
  }

  return phi[0] - 1.; // phi(b) = 1.
}

double AnalitSol(double r) {
  return 1. - .5* (r + 2) *exp(-r);
}
