// my_root_finders.cpp
#include "my_rootfinders.h"

#define DEBUG    0

int Bisection (double (*func)(double), double a, double b, double xacc, double &zero, int &iter) {
  ///////////////////////////////////////////////////////////////////
  /// func(in)   function to be searched for roots
  /// a(in)      beginning of the interval
  /// b(in)      end of the interval
  /// xacc(in)    xaccerance on the zero 
  ///
  /// zero(out)  the central value of the final interval containing the zero
  /// iter(out)  the total number of iterations
  ///////////////////////////////////////////////////////////////////

  // bisogna metterci tutti i controlli, del tipo se ti esce nan
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
  double delta = 1; // Relative Error

  xbeg = a;
  xend = b;
  fbeg = func(xbeg);
  fend = func(xend);

  if ( fbeg*fend > 0.) {
    cout << "! (Bisection) f(a) * f(b) > 0, Bisection can't proceed";
    return 1;

  }else if ( fbeg == 0.) {
    zero = a;
    return 0;

  }else if ( fend == 0.) {
    zero = b;
    return 0;
  }

  for (iter = 0; delta >= xacc; iter++) {
    xc = (xbeg + xend) * .5;
    fc = func(xc);

    if (fbeg*fc < 0) {
      xend = xc;
      fend = fc;

    }else if (fbeg*fc > 0) {
      xbeg = xc;
      fbeg = fc;

    }else{
      if (fbeg==0) {
        zero = xbeg;
        return 0;

      }else if (fc==0) {
        zero = xc;
        return 0;
      }
    }
    delta *= .5;

    #if DEBUG == 1
      cout << "Bisection(): iteration = " << iter;
      cout << "; [a,b] = [" << xbeg << ", " << xend << "]; ";
      cout << "xm = " << xc << "; dx = " << delta << "; ";
      cout << "fm = " << func(xc) << endl;
    #endif
  }
  zero = (xbeg + xend) / 2.;

  return 0;
}

int FalsePos (double (*func)(double), double a, double b, double xacc, double &zero, int &iter) {
  // still need check on number of iterations and accuracy on f (the same on the other finedrs)
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
  double delta = 1; // Relative Error

  xbeg = a;
  xend = b;

  fbeg = func(a);
  fend = func(b);

  for (iter = 0; delta >= xacc; iter++) {
    xc = (fbeg*xend - xbeg*fend) / (fbeg - fend);
    fc = func(xc);

    if (fbeg*fc < 0) {
      delta = abs(xend - xc);
      xend = xc;
      fend = fc;

    }else{
      delta = abs(xbeg - xc);
      xbeg = xc;
      fbeg = fc;
    }

    #if DEBUG == 1
      cout << "FalsePos(): iteration = " << iter << "; ";
      cout << "xa = " << xbeg << "; xb = " << xend << "; ";
      cout << "dx = " << delta << "; ";
      cout << "fm = " << fc << "; ";
      cout << "|del| = " << delta << endl; 
    #endif

  }

  zero = (xbeg + xend) / 2.;
  return 0;
}

int Secant (double (*func)(double), double a, double b, double xacc, double &zero, int &iter) {
  using namespace std;
  cout << setiosflags(ios::scientific);
  // diamo come guess gli estremi dl'intervallo, poi bisognerebbe implementare dei check (per il pb che esce dl'intervallo)

  // Checks
    if ( a > b ) cout << "Warning: interval reversed, left boundary > right boundary. Proceding nonetheless...";

  int k; // Iteration Indx
  double xa, xb;
  double fa, fb;
  double delta = xb - xa; // Interval (anche se qua è un po' tutto mal def pké ci muoviamo un parecchio passonda do 1 secante all'altra)

  xa = a;
  xb = b;
  fa = func(a);
  fb = func(b);

  // nn c'è alcun criterio con cui scartare 1 estremo piuttosto che l'altro, soprattutto se ripensi che qsta roba NN ha bisogno del segno per funzionare e si riesce anche a portarla sui complessi
  for (k = 0; abs(delta) > xacc; k++) { // abs() è indispensabile pké a priori nn hai il controllo di come passeggiano gli estremi e qndi potrebbero tranquillamente invertirsi
//  cout << "Secant(): k = " << k << "; xa = " << xa << "; xb = " << xb << "; dx = " << delta << endl; 

    delta = fb * ( xb - xa ) / ( fb - fa);
    xa = xb;
    fa = fb;
    xb -= delta;
    fb = func(xb);
  }
//cout << "Secant(): k = " << k << "; xa = " << xa << "; xb = " << xb << "; dx = " << delta << endl; 

  iter = k;
  zero = (xa + xb) /2.;
  return 0;
}


int Newton (double (*func)(double), double (*func1)(double), double a, double b, double xacc, double &zero, int &iter) {
  using namespace std;
  cout << setiosflags(ios::scientific);

  int k; // loop indx
  double xc, xd; // l'idea è che xc sia il passo precedente e xd sia il seguente
  double f, f1;
  double delta;

  // Initialization
    xd = (b + a ) / 2.; // qsta è la guess
    f = func(xd);
    f1 = func1(xd);
    delta = b - a;

  for (k = 0; abs(delta) > xacc; k++) {
    delta = f / f1;
    xc = xd - delta;
//  cout << "Newton(): k = " << k << "; xc = " << xc << "; dx = " << delta << endl; 
    f = func(xc);
    f1 = func1(xc);
    xd = xc;
  }

  zero = (xc + xd) / 2.; // qsto è 1 po' stupido pké xc è già stato aggiornato qndi zero = xc (nn che sia 1 grosso danno)
  iter = k;
  return 0;
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
