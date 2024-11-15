// my_root_finders.cpp
#include "my_rootfinders.h"

int Bisection (double (*func)(double), double a, double b,
               double xacc, double facc, double &zero, int &iter) {
  ///////////////////////////////////////////////////////////////////
  /// The algorithm will find the 0 for sure if there is one
  /// It is bracketed, so the search won't ever exit (a,b)
  /// func  [in]   function to be searched for roots
  /// a     [in]   beginning of the interval
  /// b     [in]   end of the interval
  /// xacc  [in]   tolerance on the zero (abscissa)
  /// facc  [in]   tolerance on the zero (ordinate)
  /// zero  [out]  midpoint of the final interval
  /// iter  [out]  total number of iterations
  ///
  /// returns  1  if the algorithm exceeds a max number of iterations
  /// returns  2  if there is no sign change at the boundaries
  ///////////////////////////////////////////////////////////////////

  using namespace std;
  cout << setiosflags(ios::scientific);

  if ( sort(a,b) ) {
    cout << "! (Bisection) The boundaries are in the wrong order.";
    cout << endl;
    cout << "Proceeding nonetheless...";
    cout << endl;
  }

  double xbeg, xend, xc;
  double fbeg, fend, fc;
  double delta = 1.; // Relative Error

  // Initialization
    xbeg = a;
    xend = b;
    fbeg = func(xbeg);
    fend = func(xend);
    iter = 0;

  if ( fbeg*fend > 0.) {
    cout << "! (Bisection) f(a) * f(b) > 0, the algorithm can't proceed";
    cout << endl;
    return 2;

  }else if ( abs(fbeg) < facc) { // Check for 0 at original boundaries
    zero = a;
    return 0;

  }else if ( abs(fend) < facc) {
    zero = b;
    return 0;
  }

  while(1){
    xc = (xbeg + xend) * .5;
    fc = func(xc);

    #if DEBUG == TRUE
      cout << "Bisection(): iteration = " << iter;
      cout << "; [a,b] = [" << xbeg << ", " << xend << "]; ";
      cout << "xm = " << xc << "; dx = " << delta << "; ";
      cout << "fm = " << func(xc) << endl;
    #endif

    // Update for next iteration (Bisection rule)
      delta *= .5;
      if (fbeg*fc < 0) {
        xend = xc;
        fend = fc;

      }else if (fbeg*fc > 0) {
        xbeg = xc;
        fbeg = fc;

      }else{ // The root must be in xc!
        zero = xc;
        return 0;
      }

    if (iter == MAX_ITERATIONS) {
      cout << "! (Bisection) Exceeded maximum number of iterations (" << iter << ")";
      cout << endl;
      cout << "Stopping the algorithm (with zero = 0.0) ...";
      cout << endl << endl;
      zero = 0.;
      return 1;
    }

    if (abs(delta) < xacc || abs(fc) < facc) {
      zero = xc;
      return 0;
    }
    delta *= .5;
    iter++;
  }
}

int FalsePos (double (*func)(double), double a, double b,
              double xacc, double facc, double &zero, int &iter) {
  ///////////////////////////////////////////////////////////////////
  /// The algorithm is bracketed
  /// func  [in]   function to be searched for roots
  /// a     [in]   beginning of the interval
  /// b     [in]   end of the interval
  /// xacc  [in]   tolerance on the zero (abscissa)
  /// facc  [in]   tolerance on the zero (ordinate)
  /// zero  [out]  root estimate (last zero, line, crossing)
  /// iter  [out]  total number of iterations
  ///
  /// returns  1  if the algorithm exceeds a max number of iterations
  /// returns  2  if there is no sign change at the boundaries
  ///////////////////////////////////////////////////////////////////

  using namespace std;
  cout << setiosflags(ios::scientific);

  if ( sort(a,b) ) {
    cout << "! (FalsePos) The boundaries are in the wrong order.";
    cout << endl;
    cout << "Proceeding nonetheless...";
    cout << endl;
  }

  double xbeg, xend, xc;
  double fbeg, fend, fc;
  double delta = 1.; // Relative Error

  // Initialization
    xbeg = a;
    xend = b;
    fbeg = func(a);
    fend = func(b);
    iter = 0;

  if ( fbeg*fend > 0.) {
    cout << "! (FalsePos) f(a) * f(b) > 0, the algorithm can't proceed";
    cout << endl;
    return 2;

  }
  else if ( abs(fbeg) < facc) {
    zero = a;
    return 0;

  }else if ( abs(fend) < facc) {
    zero = b;
    return 0;
  }

  while(1){
    xc = (fbeg*xend - xbeg*fend) / (fbeg - fend); // False position rule
    fc = func(xc);

    #if DEBUG == TRUE
      cout << "FalsePos(): iteration = " << iter << "; ";
      cout << "xa = " << xbeg << "; xb = " << xend << "; ";
      cout << "dx = " << delta << "; ";
      cout << "fm = " << fc << "; ";
      cout << "|del| = " << delta << endl; 
    #endif

    // Update for next iteration
      if (fbeg*fc < 0) {
        delta = abs(xend - xc);
        xend = xc;
        fend = fc;

      }else if (fbeg*fc > 0) {
        delta = abs(xbeg - xc);
        xbeg = xc;
        fbeg = fc;

      }else{ // The root must be in xc!
      zero = xc;
      return 0;
    }

    if (iter == MAX_ITERATIONS) {
      cout << "! (FalsePos) Exceeded maximum number of iterations (" << iter << ")";
      cout << endl;
      cout << "Stopping the algorithm (with zero = 0.0) ...";
      cout << endl << endl;
      zero = 0.;
      return 1;
    }

    if (abs(delta) < xacc || abs(fc) < facc) {
      zero = xc;  // Last zero (line) crossing
      return 0;
    } iter++;
  }
}

int Secant (double (*func)(double), double a, double b, 
            double xacc, double facc, double &zero, int &iter) {
  ///////////////////////////////////////////////////////////////////
  /// Successive algorithm (a is the first point of the series)
  /// There is no bracketing involved or sign check,
  /// it can therefore generalize to complex numbers and multid
  ///
  /// func  [in]   function to be searched for roots
  /// a     [in]   beginning of the interval
  /// b     [in]   end of the interval
  /// xacc  [in]   tolerance on the zero (abscissa)
  /// facc  [in]   tolerance on the zero (ordinate)
  /// zero  [out]  root estimate (last point of the series)
  /// iter  [out]  total number of iterations
  ///
  /// returns  1  if the algorithm exceeds a max number of iterations
  /// returns  2  if the algorithm converges out of (a,b)
  ///////////////////////////////////////////////////////////////////

  using namespace std;
  cout << setiosflags(ios::scientific);

  if ( sort(a,b) ) {
    cout << "! (Secant) The boundaries are in the wrong order.";
    cout << endl;
    cout << "Proceeding nonetheless...";
    cout << endl;
  }

  // Check for 0 at the boundaries
    if (abs(func(a)) < facc) {
      zero = a;
      return 0;

    }else if (abs(func(b)) < facc) {
      zero = b;
      return 0;
    }

  double x0, x1;
  double f0, f1;
  double delta = b - a;

  // Initialization
    x0 = a;
    x1 = b;
    f0 = func(a);
    f1 = func(b);
    iter = 0;

  while(1){
    delta = f1 * ( x1 - x0 ) / ( f1 - f0 );
    x0 = x1;      // Update befor changing x1
    x1 -= delta;  // Secant rule

    #if DEBUG == TRUE
      cout << "Secant(): iteration = " << iter << ";";
      cout << "xa = " << x0 << "; xb = " << x1 << "; ";
      cout << "dx = " << delta << endl; 
    #endif

    // Update for next iteration
      f0 = f1;
      f1 = func(x1);


    if (iter == MAX_ITERATIONS) {
      cout << "! (Secant) Exceeded maximum number of iterations (" << iter << ")";
      cout << endl;
      cout << "Stopping the algorithm (with zero = 0.0) ...";
      cout << endl << endl;
      zero = 0.;
      return 1;
    }
   
    if (abs(delta) < xacc || abs(f1) < facc) {
      zero = x1; // Last point of the series
      
      if (zero < a || zero > b) {
        cout << "! (Secant) Converged to zero out of original interval";
        cout << endl;
        return 2;
      }
      return 0;
    } iter++;
  }
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

  if ( sort(a,b) ) {
    cout << "! (Newton) The boundaries are in the wrong order.";
    cout << endl;
    cout << "Proceeding nonetheless...";
    cout << endl;
  }

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

    #if DEBUG == TRUE
      cout << "Newton(): iteration = " << iter << ";";
      cout << "x0 = " << x0 << "; dx = " << delta;
      cout << endl; 
    #endif

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



// UTILITIES
int sort(double& a, double& b) {
  ///////////////////////////////////////////////////////////////////
  /// if a < b return 0, else it swaps them in place and returns 1
  ///////////////////////////////////////////////////////////////////

  double t;
  if (a < b){
    return 0;
  } else {
    t = a;
    a = b;
    b = t;
    return 1;
  }
}
