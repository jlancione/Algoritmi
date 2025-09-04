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
#define G   9.81
#define NEQ  4

#define PENDULUM 0

void dYdt ( double t, double *theta, double *R );

int main () {
  using namespace std;
  cout << setiosflags(ios::scientific);

  // initialize
  double theta[NEQ];

  theta[0] = M_PI-M_PI_4;  // theta1 (rad)
  theta[1] = M_PI;  // theta2 (rad)
  theta[2] = 0.0 ;  // dtheta1
  theta[3] = 0.0 ;  // dtheta2

  // time step size
  double tmax, tmin, dt, t ;
  tmax = 40.0;
  tmin = 0.0;
  dt = 0.01;
  int nsteps = (tmax-tmin)/dt;
  cout << "nsteps = " << nsteps << endl;

  ofstream fdata;
  #if PENDULUM == 0
    fdata.open("double_pendulum.dat");
  #endif
  #if PENDULUM == 1
    fdata.open("double_pendulum1.dat");
  #endif

  int stepindx, eqindx;

  int cnt = 0;   // auxiliary counter for flips
  int flipcnt=0, flipflag=1;

  double x, x0, y, E;
  for(stepindx = 0; stepindx <= nsteps; stepindx++) {
    t = stepindx*dt;

    // Write on disk
    x = sin(theta[0]); // Cartesian coord
    y = -cos(theta[0]);
    E = y*y*G;              // potential energy 1st pendulum
    E += theta[2]*theta[2]; // kinetic energy
    fdata << t << " " << x << " " << y;

    // Flip check
    if ( y>0 && x*x0<0 ) {
      flipflag *= -1;
      if ( cnt>10 && flipflag<0 ) {
        flipcnt += 1;
        flipflag = 1;
        cnt = 0;
      }
    }
    else cnt += 1;

    x0 = x;

    // Finish writing on disk
    x += sin(theta[1]);
    y += -cos(theta[1]);
    E += y*y*G;             // potential energy 2 pendulum
    E += theta[3]*theta[3]; // kinetic energy
    fdata << " " << x << " " << y << " " << E << endl;

    RK4Step(t, theta, dYdt, dt, NEQ);

  }
  cout << "Number of flips = " << flipcnt << endl;

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
