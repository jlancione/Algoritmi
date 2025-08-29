//  Integrare le eq dl moto
//  is energy conserved
//  range of initial conditions that lead to chaos
//  does the pendulum flip?
#include <cmath>
#include <iostream>
#include <iomanip>
// #include "my_odesolvers.h"


// g / L
#define GL  9.81
#define NEQ  2

void dYdt ( double t, double *theta, double *R );

int main () {
  using namespace std;
  cout << setiosflags(ios::scientific);

  // initialize
  double theta[NEQ*2];
  // angoli in radianti?
  theta[0] = ;  // theta1
  theta[1] = ;  // theta2
  theta[2] = 0.0 ;  // dtheta1
  theta[3] = 0.0 ;  // dtheta2

  // time step size
  double tmax, tmin, dt, t ;
  int nsteps = 200;
  tmax = 20.0;
  tmin = 0.0;
  dt = (tmax - tmin) / (double)nsteps;
  cout << "dt = " << dt << endl;

  // set initial values

  // error tracking

  
  // ofstream fdata;
  // fdata.open("double_pendulum.dat");

  int stepindx, eqindx;

  for(stepindx = 0; stepindx <= nsteps; stepindx++) {
    t = stepindx*dt;

    for(eqindx=0; eqindx < NEQ; eqindx++) {
      // error computation
    }
    RK4Step(t, theta, dYdt, NEQ);

    // write on disk
    fdata << t << " " << theta[0] << " " << theta[2] << endl;

  }

  fdata.close();

  return 0;
}

void dYdt ( double t, double *theta, double *R ) {
  // m1 = m2
  double num, denom ;

  num = GL* 3. * sin(theta[0]) - GL*sin(theta[0]- 2.*theta[1]) - 2.*sin(theta[0]-theta[1])* (theta[3]*theta[3] + theta[2]*theta[2]*cos(theta[0]-theta[1])) ;
  denom = 3. - cos(2.(*theta[0] - theta[1]));
  R[0] = theta[2];
  R[2] = num / denom;

  num = sin(theta[0] -theta[1])*(2*theta[2]*theta[2] + 2*GL* cos(theta[0]) + theta[3]*theta[4]* cos(theta[0] - theta[1])) ;
  denom = 3 - cos(2*(theta[0] - theta[1])) ;
  R[1] = theta[3];
  R[3] = num / denom;


  // Video su gnuplot
  // produrre il file con i .i dla simulazione



}
