#include <iostream>
#include <iomanip>
#include <cmath>

#define MAX_ITERATIONS   128

double Acceleration (double);
double Velocity (double);
int GaussRule (double (*)(double), double, double,
               int, int, double&);
int Newton (double (*)(double), double (*)(double), 
            double, double, double, double, double &, int &);

int main() {
  using namespace std;

  double tol = 1.e-6; // for the root finder
  double tstar;
  int iter;

  Newton(Velocity, Acceleration, 0., 10., tol, tol, tstar, iter);
  cout << "Inversion point at time = " << tstar;
  cout << endl;

  return 0;
}


double Acceleration (double t) {
  return (1. - exp(-t)) / sqrt(1. + t*t*t*t);
}

double Velocity (double t) {
  using namespace std;
  static int nfv = 0; // Cumulative number of function evaluations
  static double v = -1.;
  double dv; 
  static double tlo = 0.;
  int ngauss = 5, nint;

  nint = ceil( abs(t-tlo)*2. );

  GaussRule(Acceleration, tlo, t, nint, ngauss, dv);
  nfv += ngauss*nint; 
  cout << "tlo = "    << tlo  << "; thi = " << t << "; nint = " << setw(2) << nint
       << "; Func eval = " << setw(3) << nfv << endl;

  v += dv;
  tlo = t;

  return v;
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


int Newton (double (*func)(double), double (*dfunc)(double), 
            double a, double b, double xacc, double facc, double &zero, int &iter) {
  ///////////////////////////////////////////////////////////////////
  /// Successive algorithm, initial guess is midpoint of the range
  /// There is no bracketing involved, the algorithm can exit (a,b)
  /// func   [in]   function to be searched for roots
  /// dfunc  [in]   derivative of the function
  /// a      [in]   beginning of the interval
  /// b      [in]   end of the interval
  /// xacc   [in]   tolerance on the zero (abscissa)
  /// facc   [in]   tolerance on the zero (ordinate)
  /// zero   [out]  root estimate (last point of the series)
  /// iter   [out]  total number of iterations
  ///
  /// returns  1  if the alorithm exceeds a max number of iterations
  /// returns  2  if the algorithm converges out of (a,b)
  ///////////////////////////////////////////////////////////////////

  using namespace std;
  cout << setiosflags(ios::scientific);

  // Check for 0 at the boundaries
    if (abs(func(a)) < facc) {
      zero = a;
      return 0;

    }else if (abs(func(b)) < facc) {
      zero = b;
      return 0;
    }

  double x0, x1;
  double f, df;
  double delta;

  // Initialization
    x0 = (b + a ) / 2.; // Initial guess
    f = func(x0);
    df = dfunc(x0);
    delta = b - a;
    iter = 0;

  while(1){
    delta = f / df;  
    x1 = x0 - delta;   // Newton rule

    // Update for next iteration
      f = func(x1);
      df = dfunc(x1);
      x0 = x1;

    if (iter == MAX_ITERATIONS) {
      cout << "! (Newton) Exceeded maximum number of iterations (" << iter << ")";
      cout << endl;
      cout << "Stopping the algorithm (with zero = 0.0) ...";
      cout << endl << endl;
      zero = 0.;
      return 1;
    }

    if (abs(delta) < xacc || abs(f) < facc) {
      zero = x1; // Last point of the series
      
      if (zero < a || zero > b) {
        cout << "! (Newton) Converged to zero out of original interval";
        cout << endl;
        return 2;
      }
      return 0;
    } iter++;
  }
}
