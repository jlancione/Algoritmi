#include <iostream>
#include <cmath>
#include <fstream>
#include "my_derivatives.h"

#define ALPHA   10

double trajectory (double);

int main() {
  using namespace std;
  ofstream fdata;
  fdata.open("trajectory.dat");

  double t, dt, x, v, a;
  double x_1, x1;
  double tmax = ALPHA, tmin = 0.;

  int i, nint = ALPHA*100;
  dt = tmax / nint;
  for(i = 0; i < nint; i++) {
    t = i*dt;
    x = trajectory(t);
    x_1 = trajectory(t -dt);
    x1  = trajectory(t +dt);

    if (i==0){ 
    // Because trajectory is singular in t=0., can't use CDerivative there
      v = FDerivative(x, x1, dt);
      double v1;
      v1 = BDerivative(x1, x, dt);
      a = FDerivative(v, v1, dt);
    }else{
      v = CDerivative(x_1, x1, dt);
      a = SecondDerivative(x, x_1, x1, dt);
    }

    fdata << t << " " << x << " " << v << " " << a;
    fdata << endl;
  }

  fdata.close();
  return 0;
}


double trajectory (double t) {
  if (t==0.) return 0.;
  else {return ALPHA*t*t - t*t*t*( 1 - exp( -ALPHA*ALPHA/t));}
}
