// my_integrals.cpp
#include "my_integrals.h"

#define DEBUG    FALSE


int RectangularRule (double (*F)(double), double a, double b, int N, double& sum){ 
  ///////////////////////////////////////////////////////////////////
  // Computes the interval dividing the area in rectangles,
  // using the leftmost point of each interval as the height
  // Error order = h^2  (h is the length of the subinterval)
  //
  // F(in)  function to integrate
  // a(in)  beginning of the interval
  // b(in)  end of interval
  // N(in)  number of intervals
  //
  /// sum(out)  returns the computed sum
  ///////////////////////////////////////////////////////////////////

  using namespace std;

  double dx;

  //Initialization
  dx = ( b - a)/(double)N;
  sum = 0.;

  for(int i=0; i<N; i++){
   sum += F(a + dx*i); 
  }
  sum *= dx;

  return 0;
}

int TrapezoidalRule (double (*F)(double), double a, double b, int N, double& sum){
  ///////////////////////////////////////////////////////////////////
  // Computes the integral dividing the area in trapezoids
  // Error order = h^3  (h is the length of the subinterval)
  //
  // F(in)  function to integrate
  // a(in)  beginning of the interval
  // b(in)  end of interval
  // N(in)  number of intervals
  //
  /// sum(out)  returns the computed sum
  ///////////////////////////////////////////////////////////////////

  using namespace std;

  double h = ( b - a)/(double)N;
  sum = 0;

  sum += ( F(a) + F(b)) / 2.;
  for(int i=1; i < N; i++){
   sum += F(a + h*i); 
  }
  sum *= h;

  return 0;
}

int SimpsonRule (double (*F)(double), double a, double b, int N, double& sum){
  ///////////////////////////////////////////////////////////////////
  /// Computes the integral approximating every interval with a parabola
  /// Subintervals are used in pairs (Simpson needs 3 points per interval)
  /// Correct for polinomials up to order 3
  /// Error order = h^5  (h is the length of 2 subintervals)
  ///
  /// F(in)     function to integrate
  /// a(in)     beginning of the interval
  /// b(in)     end of the interval
  /// N(in)     number of intervals
  /// 
  /// sum(out)  returns the computed sum
  ///////////////////////////////////////////////////////////////////

  using namespace std;

  if (N % 2 == 1) {
    cout << "! (SimpsonRule) The number of intervals must be even" << endl;
    cout << "Proceeding nonetheless (+1)...";
    cout << endl;
  }

  double h = ( b - a) / (double)N;
  sum = 0;

  double w = 4.0;

  for(int i=1; i < N; i++){                
    sum += F(a + h*i) * w;  
    w = 6.0 - w;
  }

  sum += F(a) + F(b);
  sum *= h;
  sum /= 3.;

  return 0;
}


int GaussRule (double (*F)(double), double a, double b, int N, int Ng, double& sum) {
  ///////////////////////////////////////////////////////////////////
  /// Correct for polinomials up to order 2Ng-1
  /// F needs to be as smooth as possible in each subinterval
  /// F(in)    Function to integrate
  /// a(in)    Beginning of the interval
  /// b(in)    End of the interval
  /// N(in)    Number of subintervals
  /// Ng(in)   Number of gaussian points per subinterval
  ///
  /// sum(out) returns the computed sum
  ///////////////////////////////////////////////////////////////////

  using namespace std;
  double w[32]; double x[32];    // initialized statically -> maximum capacity for the function

  if (Ng == 1) {
    x[0] = 0.;            w[0] = 2.;

  } else if (Ng == 2) {
    x[0] = sqrt(1. / 3.); w[0] = 1.;
    x[1] = -x[0];         w[1] = w[0];

  } else if (Ng == 3) {
    x[0] =           0  ; w[0] = 8. / 9.;
    x[1] = sqrt(3. / 5.); w[1] = 5. / 9.;
    x[2] = -x[1];         w[2] = w[1];

  } else if (Ng == 4) {
    x[0] = sqrt( (3. - 2.*sqrt(6./5.))/ 7.); w[0] = (18. + sqrt(30) ) / 36.;
    x[1] = -x[0];                           w[1] = w[0];
    x[2] = sqrt( (3. + 2.*sqrt(6./5.))/ 7.); w[2] = (18. - sqrt(30) ) / 36.;
    x[3] = -x[2];                           w[3] = w[2];

  } else if (Ng == 5) {
    x[0] = 0; w[0] = 128. / 225.;
    x[1] = sqrt(5. - 2.*sqrt(10./7.)) / 3.; w[1] = (322. + 13.*sqrt(70) ) / 900.;
    x[2] = -x[1];                           w[2] = w[1];
    x[3] = sqrt(5. + 2.*sqrt(10./7.)) / 3.; w[3] = (322. - 13.*sqrt(70) ) / 900.;
    x[4] = -x[3];                           w[4] = w[3];

  } else {
    cout << "! (GaussRule) NOT defined for ngauss = " << Ng << endl;
    return 1;
  }

  double xeval;     // evaluation point for f
  double x0, x1;    // beginning and end of subinterval
  double xmean;     // mean point of the subinverval
  double subsum;    // partial sum (over subinterval)

  double dx = (double)(b - a) / (double)N;

  // Initialize boundaries and sum
  sum = 0.0;
  x0 = a;
  x1 = a + dx;

  for(int j = 1; j <= N; j++) {    // Loop over subintervals
    xmean = (x0 + x1) / 2.;
    subsum = 0.0;

    for(int i = 0; i < Ng; i++) {  // Apply gaussian rule
      xeval = (dx * x[i]) / 2.;
      xeval += xmean;
      subsum += F(xeval) * w[i];

      #if DEBUG  == 1
        cout << "ascissa = " << x[i] << endl;
        cout << "peso = " << w[i] << endl;
        cout << "xeval = " << xeval << endl;
        cout << "F(xeval) = " << F(xeval) << endl;
        cout << "subsum = " << subsum << endl;
        cout << endl;
      #endif
    }
    subsum *= dx;
    subsum /= 2.;

    sum += subsum;

    // Update boundaries
    x0 = x1;
    x1 = a + (j + 1)*dx;
  }

  return 0;
}
