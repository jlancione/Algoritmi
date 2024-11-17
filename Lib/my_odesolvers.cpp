#include "my_odesolvers.h"

#define NEQ_MAX    10

void EulerStep (double t, double * Y, void (*RHSFunc)(double, double *, double *),
                double h, int neq) {
  ///////////////////////////////////////////////////////////////////
  /// Computes a step with EULER rule 
  /// Single step linear method -> local error is h^2
  ///
  /// t        [in]      t_n starting time of the step
  /// Y        [in/out]  (in) solution at t_n, (out) sol at t_n+1
  /// RHSFunc  [in]      right hand side, ie dYdt (pointer to func)
  /// h        [in]      time step
  /// neq      [in]      number of equations in the system
  ///////////////////////////////////////////////////////////////////
  double k[NEQ_MAX];
  int i;
    
  RHSFunc(t, Y, k);  // Compute increment
  for (i = 0; i < neq; i++) Y[i] += h * k[i];  // Update Y
}


void RK2Step (double t, double * Y, void(*RHS_Func)(double, double *, double *),
              double h, int neq) {
  ///////////////////////////////////////////////////////////////////
  /// Computes a step with RUNGE-KUTTA 2 rule
  /// 2nd Order accurate (h^3 local error)
  /// 2 RHS evaluation per interval, single step method
  ///
  /// t        [in]      t_n starting time of the step
  /// Y        [in/out]  (in) solution at t_n, (out) sol at t_n+1
  /// RHSFunc  [in]      right hand side, ie dYdt (pointer to func)
  /// h        [in]      time step
  /// neq      [in]      number of equations in the system
  ///////////////////////////////////////////////////////////////////
  double Y1[NEQ_MAX], k1[NEQ_MAX], k2[NEQ_MAX];
  int i;

  RHS_Func(t, Y, k1);         // Compute first increment

  for (i = 0; i < neq; i++) Y1[i] = Y[i] + .5*h * k1[i];
  RHS_Func(t + .5*h, Y1, k2); // Compute second increment

  for (i = 0; i < neq; i++) Y[i] += h * k2[i]; // Update Y
}


void RK4Step (double t, double * Y, void(*RHS_Func)(double, double *, double *),
              double h, int neq) {
  ///////////////////////////////////////////////////////////////////
  /// Computes a step with RUNGE-KUTTA 4 rule
  /// 4th Order accurate (h^5 local error) 
  /// 4 RHS evaluation per interval, single step method
  ///
  /// t        [in]      t_n starting time of the step
  /// Y        [in/out]  (in) solution at t_n, (out) sol at t_n+1
  /// RHSFunc  [in]      right hand side, ie dYdt (pointer to func)
  /// h        [in]      time step
  /// neq      [in]      number of equations in the system
  ///////////////////////////////////////////////////////////////////
  double Y1[NEQ_MAX], k1[NEQ_MAX], k2[NEQ_MAX], k3[NEQ_MAX], k4[NEQ_MAX];
  int i;

  RHS_Func(t, Y, k1);         // Compute first increment

  for (i=0; i < neq; i++) Y1[i] = Y[i]+ .5*h * k1[i];
  RHS_Func(t + .5*h, Y1, k2); // Compute second increment

  for (i=0; i < neq; i++) Y1[i] = Y[i]+ .5*h * k2[i];
  RHS_Func(t + .5*h, Y1, k3); // Compute third increment

  for (i=0; i < neq; i++) Y1[i] = Y[i]+ h * k3[i];
  RHS_Func(t + h, Y1, k4);    // Compute fourth increment

  // Update Y
  for (i=0; i < neq; i++) Y[i] += h/6. *(k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
}


void PosVerletStep (double *x, double *v, void (*Acceleration)(double*, double *),
                double h, int npos) {
  ///////////////////////////////////////////////////////////////////
  /// Computes a step with Position VERLET rule (Simplectic)
  /// Thought to solve Newton's equation,
  /// it is time reversible and conserves energy
  /// 2nd Order accurate (h^3 local error) 
  /// 1 acceleration evaluation per interval, single step method
  ///
  /// t             [in]      t_n starting time of the step
  /// Y             [in/out]  (in) solution at t_n, (out) sol at t_n+1
  /// Acceleration  [in]      right hand side, ie dYdt (pointer to func)
  /// h             [in]      time step (CONSTANT! for it to be 2nd order)
  /// npos          [in]      lenght of x and v
  ///////////////////////////////////////////////////////////////////
  int k;
  double acc[NEQ_MAX];

  for(k = 0; k < npos; k ++) { // Loop on positions
    x[k] += .5*h * v[k]; // Update positions (half step)
  }
  Acceleration(x, acc);
  for(k = 0; k < npos; k ++) { // Loop on velocities
    v[k] += h * acc[k]; // Update velocities (full step)
  }
  for(k = 0; k < npos; k ++) { // Loop on positions
    x[k] += .5*h * v[k]; // Update positions (full step)
  }
}

