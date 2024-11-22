#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "my_odesolvers.h"
#include "my_rootfinders.h"

#define NINT    1000
#define SESSION   2

// qnti intervalli usano per il bracketing? qlo inficia la precisione del mio Bisection
// il loro bisection cosa restituisce? xc dl'intervallo finale trovato o qlo 1a?
// bisection esce giusto e nn fa scherzi
// facendo prove la cosa nn dipende da RK4 (nel senso che anche raffinandolo con + intervalli a me nn cambia molto... però a lui camibiava, e anche perecchio, passava da 1e-8 a 1e-10... siamo lontani)
// al contrario sembra che per loro nn dipenda dl bracketing (pké ness1 ha mai detto il numero di intervalli, ma concordano tutti il che mi fa credere abbiano scritto Bisection usando l'errore assoluto come delta per uscire)

void RHSide (double, double *, double *);
double Residual (double);
void InitialConditions(double *, double);


int main() {
  using namespace std;
  cout << setiosflags(ios::scientific);
  cout << setprecision(8);
  ofstream fdata;
  fdata.open("wave.dat");

  double x, x0, x1, dx;
  // Boundaries
    x0 = 0.;
    x1 = 1.;

  dx = ( x1 - x0 ) / double(NINT);

  int neq = 3; // phi, dphi, k
  double phi[neq]; // phi = {phi, dphi, k};

  int i, j;

  #if SESSION == 1
    // In gnuplot> load "waves.gp"
    double k;
    for (j = 0; j < 5; j++) {
      k = 1. + j;
      InitialConditions(phi, k);

      for (i = 0; i < NINT; i++) {
        x = i*dx;
        RK4Step(x, phi, RHSide, dx, neq);
        fdata << x << " " << phi[0] << endl;
      }
    fdata << endl << endl;
    }
  #endif

  #if SESSION == 2
    int nzeros;
    double k[32], xL[32], xR[32];

    nzeros = Bracket(Residual, 1., 20., 200, xL, xR);

    int status, iter;
    for (i = 0; i < nzeros; i++) {
      status = Bisection(Residual, xL[i], xR[i], 1.e-9, 1.e-9, k[i], iter);
      if (status == 1) {
        cout << "Bisection did NOT converge" << endl;
      }
      if (status == 0) {
        cout << "Bisection converged in " << iter << " iterations";
        cout << endl;
        cout << "Eigenvalue k is " << k[i] << "; ";
        cout << "|k - " << i + 1 << "pi| = " << abs(k[i] - M_PI*(i+1)) << endl;
      }
    }

    // Plot sines
    // In gnuplot> load "sines.gp"
    for (i = 0; i < nzeros; i++) {
      InitialConditions(phi, k[i]);

      for (j = 0; j < NINT; j++) {
        x = j*dx;
        RK4Step(x, phi, RHSide, dx, neq);
        fdata << x << " " << phi[0] << endl;
      }
      fdata << endl << endl;
    }
  #endif  

  fdata.close();
  return 0;
}


void RHSide (double x, double *Y, double *R) {
  // x is not involved, Y[2] = k
  R[0] = Y[1];
  R[1] = - Y[2]*Y[2]* Y[0];
  R[2] = 0.;
}

// This is also problem specific
double Residual (double k) {
  double x, x0, x1, dx;
  // Boundaries
    x0 = 0.;
    x1 = 1.;

  dx = ( x1 - x0 ) / (double)NINT;

  int neq = 3; // phi, dphi, k

  double phi[neq];
  InitialConditions(phi, k);

  int i;
  for (i = 0; i < NINT; i++) {
    x = i*dx;
    RK4Step(x, phi, RHSide, dx, neq);
  }

  return phi[0] - x0;
}

void InitialConditions(double *Y, double k) {
  Y[0] = 0.;
  Y[1] = 1.; // This is arbitrary
  Y[2] = k;
}
