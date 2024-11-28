#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "my_odesolvers.h"
#include "my_rootfinders.h"

#define NINT    800
#define SESSION   2

void RHSide (double, double *, double *);
double Residual (double);
void InitialConditions (double *, double);


int main() {
  using namespace std;
  ofstream fdata;
  fdata.open("qho.dat");

  double x, x0, x1, dx;
  // Boundaries
    x0 = -10.;
    x1 =  10.;

  dx = abs( x1 - x0 ) / double(NINT);

  int neq = 3; // psi, dpsi, E
  double psi[neq]; // psi = {psi, dpsi, E};

  int i;

  #if SESSION == 1
  // In gnuplot> load "divergence_qho.gp"
  double E;
  E = .5;  // Exact Eigenvalue for the ground state
  // Forward integration
    psi[0] = exp(-x0*x0 *.5);
    psi[1] = -x0* exp(-x0*x0 *.5);
    psi[2] = E;

    for (i = 0; i < NINT; i++) {
      x = x0 + i*dx;
      RK4Step(x, psi, RHSide, dx, neq);
      fdata << x << " " << psi[0] << endl;
    }
    fdata << endl << endl;

  // Backward integration
    dx *= -1;
    x0 =  10.;
    x1 = -10.;

    psi[0] = exp(-x0*x0 *.5);
    psi[1] = -x0* exp(-x0*x0 *.5);
    psi[2] = E;

    for (i = 0; i < NINT; i++) {
      x = x0 + i*dx;
      RK4Step(x, psi, RHSide, dx, neq);
      fdata << x << " " << psi[0] << endl;
    }
  #endif

  #if SESSION == 2
    double E, res;
    int npoints = 1e4;
    double Emax = 5.;

    for (i = 0; i < npoints; i++) {
      E = i* Emax/ (double)npoints;
      res = Residual(E);
      fdata << E << " " << res << endl;
    }
    int status, nzeros, iter;
    double xR[64], xL[64], eigenvalue;

    nzeros = Bracket( Residual, 0., Emax, 20, xL, xR);
    cout << "Eigenvalues found = " << nzeros << endl;
    for (i = 0; i < nzeros; i++) {
      status = Bisection( Residual, xL[i], xR[i], 1.e-9, 1.e-9, eigenvalue, iter);
      cout << eigenvalue << endl;
    }
  #endif


  fdata.close();
  return 0;
}


void RHSide (double x, double *Y, double *R) {
  // Y[2] = E
  R[0] = Y[1];
  R[1] = (- 2*Y[2] + x*x) *Y[0];
  R[2] = 0.;
}

// This is also problem specific
double Residual (double E) {
  double x, x0, x1, xm, dxR, dxL;
  x0 = -10.;
  x1 =  10.;
  xm =  .5;  // Matching point

  int nL, nR;
  nL = NINT;
  nR = NINT;
  dxL =  abs( x0 - xm ) / (double)nL;  // For forward integration
  dxR = -abs( xm - x1 ) / (double)nR;  // For backward integration

  int neq = 3; // psi, dpsi, E
  double psiFwd[neq], psiBck[neq];
  psiFwd[2] = E;

  int i;
  // Forward integration
    InitialConditions(psiFwd, x0);

    for (i = 0; i < NINT; i++) {
      x = x0 + i*dxL;
      RK4Step(x, psiFwd, RHSide, dxL, neq);
    }

  // Backward integration
    InitialConditions(psiBck, x1);

    for (i = 0; i < NINT; i++) {
      x = x1 + i*dxR;
      RK4Step(x, psiBck, RHSide, dxR, neq);
    }

  double d = 1.;
  double A, B;
  A = psiFwd[0]*psiBck[1];
  B = psiFwd[1]*psiBck[0]; 
  d = sqrt(A*A + B*B);

//return psiFwd[0] - psiBck[0];  // Do not use abs() you don't want spikes in your function
  return ( A - B ) / d;
}



void InitialConditions(double *Y, double x0) {
  Y[0] = 0.;  // Boundary value is the same for both sides
  Y[1] = -x0* exp(-x0*x0 *.5);  // Giving as guess the gaussian behaviour of the ground state
}
