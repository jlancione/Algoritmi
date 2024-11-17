#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include "my_odesolvers.h"

#define NTURN_POINTS    2
#define ORBIT_DEBUG    FALSE

void RHS(double, double *, double *);

int main() {
  using namespace std;

  ofstream fdata;
  fdata.open("kepler.dat");

  int neq = 4;
  double Y[4];
  // Initial conditions
  double x0, y0, vx0, vy0, alpha;
  x0 = 4.;
  y0 = 0.;
  vx0 = 0.;
  alpha = 0.3;  // for alpha < 2 the orbit should close,
  // but with alpha < .5 (approx) it doesn't really... is it the algorithm?
  // Yeah, with RK2 or Euler it gets awful...
  vy0 = sqrt(alpha/x0);

  Y[0] = x0;
  Y[1] = y0;
  Y[2] = vx0;
  Y[3] = vy0;

  double t = 0.;
  double dt = sqrt(Y[2]*Y[2] + Y[3]*Y[3]) / sqrt(Y[0]*Y[0] + Y[1]*Y[1]);
  int nturn_points = 0;
  double v_x, r0;

//while (t < 150.){
  while (nturn_points < NTURN_POINTS) {
    v_x = Y[2]; // store in memory the v_x from the previous step
    EulerStep(t, Y, RHS, dt, neq);

    if (v_x*Y[2] <= 0.) { // Turning point condition as a zero crossing
      nturn_points += 1;
      cout << "half orbit done..." << endl;

      #if ORBIT_DEBUG == TRUE
        cout << "Turning point number " << nturn_points << ": t = " << t << "; r0 = " << r0 << "; v = " << sqrt(Y[2]*Y[2] + Y[3]*Y[3]) << endl;
      #endif
    }
    fdata << Y[0] << " " << Y[1] << " " << Y[2] << " " << Y[3] << endl;

    // Update dt: \propto r/v to keep dtheta approx constant
    dt = .2* sqrt(Y[0]*Y[0] + Y[1]*Y[1] / Y[2]*Y[2] + Y[3]*Y[3]);
    t += dt;
  }
  fdata.close();
  return 0;
}



void RHS(double t, double *Y, double *R) {
  double x = Y[0];
  double y = Y[1];
  double inv = 1. / ((x*x + y*y)*sqrt(x*x + y*y));  // r^(-3/2)

  R[0] = Y[2];
  R[1] = Y[3];
  R[2] = -x * inv;
  R[3] = -y * inv;
}
