#include <iostream>
#include <cmath>
#include <iomanip>
#include "my_odesolvers.h"

#define EULER    1
#define RK2      2
#define RK4      3

#define PROBLEM  2
#define METHOD  RK2
#define DEBUG    0

#if PROBLEM == 1
  #define NEQ    1
#endif
#if PROBLEM == 2
  #include <fstream>
  #define NEQ    2
#endif


void dYdt (double t, double *Y, double *R);
void AnaliticSol (double t, double *Y);

int main() {
  using namespace std;
  cout << setiosflags(ios::scientific);

  double a, b, t, dt, tmin, tmax;
  int stepindx, nsteps, eqindx;
  double Y[NEQ], Y_analit[NEQ];
  double abs_err, rel_err;

  // Integration range and initial conditions
    #if PROBLEM == 1
      tmin = 0.;
      tmax = 3.;
      Y[0] = 1.;

      dt = .5; // try .2, .1, .05, .01, .005, .001
      nsteps = (tmax - tmin) / dt;
    #endif

    #if PROBLEM == 2
      tmin = 0.;
      tmax = 20.*M_PI;
      Y[0] = 1.;
      Y[1] = 0.;

      nsteps = 200;
      dt = tmax / (double)nsteps;
      double energy;
      ofstream fdata;
      #if METHOD == EULER
        fdata.open("conserved_euler.dat");
      #endif
      #if METHOD == RK2
        fdata.open("conserved_rk2.dat");
      #endif
      #if METHOD == RK4
        fdata.open("conserved_rk4.dat");
      #endif
    #endif

  nsteps = (tmax - tmin) / dt;

  cout << "Method: ";
  #if METHOD == EULER
    cout << "EULER";
  #endif
  #if METHOD == RK2
    cout << "RK2";
  #endif
  #if METHOD == RK4 
    cout << "RK4";
  #endif
  cout << "; dt = " << dt << endl;

  cout << setw(6) << "#  "
       << setw(8) << "t  " 
       << setw(9) << "#eq "
       << setw(15) << "y(t)  ";
  #if DEBUG == 1
  cout << setw(15) << "y_analitic  ";
  #endif
  cout << setw(15) << "abs_err  " 
       << setw(15) << "rel_err  " << endl;


  for(stepindx = 0; stepindx <= nsteps; stepindx++){
    t = stepindx*dt;
    // At every iteration every method computes Y_n+1 using t_n
    // so first I have to print everything then update them both,
    // Y with EulerStep and t with the loop
    AnaliticSol(t, Y_analit);
    cout << setw(4) << stepindx << ". " << t << "  ";

    for(eqindx=0; eqindx < NEQ; eqindx++){
      abs_err = abs(Y_analit[eqindx] - Y[eqindx]);
      rel_err = abs_err / Y_analit[eqindx];

      if(eqindx!=0) cout << setw(20) << "";
      cout << eqindx << ". "
           << setw(13) << setprecision(6) << Y[eqindx] << "  ";
      #if DEBUG == 1
        cout << setw(13) << setprecision(6) << Y_analit[eqindx] << "  ";
      #endif
      cout << setw(13) << setprecision(6) << abs_err << "  "
           << setw(13) << setprecision(6) << rel_err << "  "
           << endl;
    }
    #if METHOD == EULER
      EulerStep(t, Y, dYdt, dt, NEQ);
    #endif
    #if METHOD == RK2
      RK2Step(t, Y, dYdt, dt, NEQ);
    #endif
    #if METHOD == RK4
      RK4Step(t, Y, dYdt, dt, NEQ);
    #endif

/*
    if(stepindx==nsteps) { // To see the last update
      stepindx++;
      t = stepindx*dt;
      cout << setw(4) << stepindx << ". " << t << "  ";
      for(eqindx=0; eqindx < NEQ; eqindx++){
        abs_err = abs(Y_analit[eqindx] - Y[eqindx]);
        rel_err = abs_err / Y_analit[eqindx];

        if(eqindx!=0) cout << setw(20) << "";
        cout << eqindx << ". "
             << setw(13) << setprecision(6) << Y[eqindx] << "  ";
        #if DEBUG == 1
        cout << setw(13) << setprecision(6) << Y_analit[eqindx] << "  ";
        #endif
        cout << setw(13) << setprecision(6) << abs_err << "  "
             << setw(13) << setprecision(6) << rel_err << "  "
             << endl;
      }
    }
    */
    #if PROBLEM == 2
      energy = Y[0]*Y[0] + Y[1]*Y[1];
      fdata << t*.5*M_1_PI << " " << energy << endl;
    #endif
  }
  #if PROBLEM == 2
    fdata.close();
  #endif

  return 0;
}

// This is problem specific
void dYdt (double t, double *Y, double *R){
  #if PROBLEM == 1
    R[0] = -t*Y[0];
  #endif
  #if PROBLEM == 2
    R[0] =  Y[1];
    R[1] = -Y[0];
  #endif

} // ocio che qsta roba nn mi sta fissando le condiz iniziali in alcun modo neh
  
void AnaliticSol (double t, double *Y) {
  #if PROBLEM == 1
    Y[0] = exp(-t*t *.5);
  #endif
  #if PROBLEM == 2
    Y[0] =  cos(t);
    Y[1] = -sin(t);
  #endif
} 
