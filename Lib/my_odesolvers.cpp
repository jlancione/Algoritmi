#include "my_odesolvers.h"

#define NEQ_MAX    10

void EulerStep (double t, double * Y, void (*RHSFunc)(double, double *, double *),
                double h, int neq) {
  ///////////////////////////////////////////////////////////////////
  /// Computes a step with EULER rule
  /// t        [in]      t_n starting time of the step
  /// Y        [in/out]  (in) solution at t_n, (out) sol at t_n+1
  /// RHSFunc  [in]      right hand side, ie dYdt (pointer to func)
  /// dt       [in]      time step
  /// neq      [in]      number of equations in the system
  ///////////////////////////////////////////////////////////////////
  double k[NEQ_MAX];
  int i;
    
  RHSFunc(t, Y, k);  // Compute increment
  for (i = 0; i < neq; i++) Y[i] += h * k[i];  // Update Y
}


void RK2Step (double t, double * Y, void(*RHS_Func)(double, double *, double *),
              double h, int neq) {
       // ho bisogno di definire Y1 pké devo mettere in memoria il passo/stima intermedia, k1 and k2 are redundant, one could use the same increment array, but ok I think it's meant to adequate with 
  double Y1[NEQ_MAX], k1[NEQ_MAX], k2[NEQ_MAX];
  int i;

  RHS_Func(t, Y, k1);         // Compute first increment

  for (i = 0; i < neq; i++) Y1[i] = Y[i] + .5*h * k1[i];
  RHS_Func(t + .5*h, Y1, k2); // Compute second increment

  for (i = 0; i < neq; i++) Y[i] += h * k2[i]; // Update Y
}

void RK4Step (double t, double * Y, void(*RHS_Func)(double, double *, double *),
              double h, int neq) {
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
