//  Integrare le eq dl moto
//  is energy conserved
//  range of initial conditions that lead to chaos
//  does the pendulum flip?
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "my_odesolvers.h"


// g / L
#define GL  9.81
#define NEQ  4

void dYdt ( double t, double *theta, double *R );

int main () {
  using namespace std;
  cout << setiosflags(ios::scientific);

  // initialize
  double theta[NEQ];

  theta[0] = M_PI_2;  // theta1 (rad)
  theta[1] = M_PI_2;  // theta2 (rad)
  theta[2] = 0.0 ;  // dtheta1
  theta[3] = 0.0 ;  // dtheta2

  // time step size
  double tmax, tmin, dt, t ;
  tmax = 6.0;
  tmin = 0.0;
  dt = 0.01;
  int nsteps = (tmax-tmin)/dt;
  cout << "nsteps = " << nsteps << endl;

  ofstream fdata;
  fdata.open("double_pendulum.dat");

  int stepindx, eqindx;

  double x,y;
  for(stepindx = 0; stepindx <= nsteps; stepindx++) {
    t = stepindx*dt;

    RK4Step(t, theta, dYdt, dt, NEQ);

    // Write on disk
    x = sin(theta[0]); // Cartesian coord
    y = -cos(theta[0]);
    fdata << t << " " << x << " " << y;
    x += sin(theta[1]);
    y += -cos(theta[1]);
    fdata << " " << x << " " << y << endl;

  }

  fdata.close();

  return 0;
}

void dYdt ( double t, double *theta, double *R ) {
  // m1 = m2
  double num, denom ;

  num = -GL* 3. * sin(theta[0]) - GL*sin(theta[0]- 2.*theta[1]) - 2.*sin(theta[0]-theta[1]) * (theta[3]*theta[3] + theta[2]*theta[2]*cos(theta[0]-theta[1])) ;
  denom = 3. - cos( 2.*(theta[0] - theta[1]) );
  R[0] = theta[2];
  R[2] = num / denom;

  num = 2*sin(theta[0] -theta[1])*( 2*theta[2]*theta[2] + 2*GL*cos(theta[0]) + theta[3]*theta[3]*cos(theta[0] - theta[1]) ) ;
  denom = 3 - cos(2*(theta[0] - theta[1])) ;
  R[1] = theta[3];
  R[3] = num / denom;

}
