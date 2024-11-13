#include <iostream>
#include <cmath>
#include <iomanip>


#define DEBUG   FALSE

int Bisection (double (*func)(double), double a, double b, double tol, double &zero, int &iter);
int FalsePos (double (*func)(double), double a, double b, double tol, double &zero, int &iter);
int Secant (double (*func)(double), double a, double b, double tol, double &zero, int &iter);
int Newton (double (*func)(double), double (*func1)(double), double a, double b, double tol, double &zero, int &iter);

int Bracket ( double (*func)(double), double a, double b, int N, double xL[], double xR[]);
double Func (double x);


int main () {
  using namespace std;

  double a = -10.;
  double b =  10.;
  int N = 10;
  int k = 0;
  double xL[N], xR[N];

  double tol = 1.e-6;
  int iter = 0;

  k = Bracket (Func, a, b, N, xL, xR);
  cout << "Number of zeros = " << k << endl;
  double zero[k];

  for (int i=0; i<k; i++) {
    Bisection( Func, xL[i], xR[i], tol, zero[i], iter);
    cout << "Found zero in: (" << xL[i] << ", " << xR[i] << "); zero at " << zero[i] << endl;
  }
  return 0;
}



// l'obiettivo è di ritornare i sottointervalli in cui c'è uno zero - SEPARA I TASK!!
int Bracket ( double (*func)(double), double a, double b, int N, double xL[], double xR[]) {
  double dx;
  double xbeg, xend;
  double fbeg, fend;

  int counter = 0; // counter for zeros

  dx = abs( b - a ) / (double)N;
  xend = a;
  fend = func(a);

  for (int i = 0; i<N; i++) {
    xbeg = xend;
    xend = xbeg + dx;
//  xbeg = a + i*dx;
//  xend = a + (i+1)*dx;
    fbeg = fend;

    fend = func(xend);

    if ( fbeg*fend <= 0) {
      xL[counter] = xbeg;
      xR[counter] = xend;

      counter ++;
    } else {
      continue;
    }
  }
  return counter;
}


int Bisection (double (*func)(double), double a, double b, double tol, double &zero, int &iter) {
  // bisogna metterci tutti i controlli, del tipo se ti esce nan e se la funzione ha gli estremi dlo stso segno sl'intervallo, cose così, intervallo rovesciato
  using namespace std;
  cout << setiosflags(ios::scientific);

  // Checks
    if ( a > b ) cout << "Warning: interval reversed, left boundary > right boundary. Proceding nonetheless...";

  int k; // Iteration Indx
  double xbeg, xend, xc;
  double delta = 1; // Relative Error
  double indx;

  xbeg = a;
  xend = b;

  // per ottimizzare mi basta ricordarmi dl valore calcolato dla funz nl'estremo che tengo
  for (k = 0; delta >= tol; k++) {
    xc = (xbeg + xend) * .5;
    indx = func(xbeg)*func(xc);

    if (indx < 0) {
      xend = xc;
    }
    else if (indx > 0) {
      xbeg = xc;
    }
    else {cout << "Hello" << endl;}
    delta *= .5;

    #if DEBUG == TRUE
//    cout << "Bisection(): k = " << k << "; [a,b] = [" << xbeg << ", " << xend << "]; xm = " << xc << "; dx = " << delta << "; fm = " << func(xc) << endl;
    #endif
  }

  zero = xc;

  return 0;
}


int FalsePos (double (*func)(double), double a, double b, double tol, double &zero, int &iter) {
  using namespace std;
  cout << setiosflags(ios::scientific);

  // Checks
    if ( a > b ) cout << "Warning: interval reversed, left boundary > right boundary. Proceding nonetheless...";

  int k; // Iteration Index
  double xbeg, xend, xc;
  double fbeg, fend, fc;
  double delta = 1; // Relative Error

  xbeg = a;
  xend = b;

  fbeg = func(a);
  fend = func(b);

  for (k = 0; delta >= tol; k++) {
    xc = (fbeg*xend + xbeg*fend) / (double)(fbeg + fend);
    fc = func(xc);

    if (fc*fbeg < 0) {
      xend = xc;
      fend = fc;
    }else{
      xbeg = xc;
      fbeg = fc;
    }
    delta = xend - xbeg;
    cout << "FalsePos(): k = " << k << "; xa = " << xbeg << "; xb = " << xend << "; dx = " << delta << endl; 
  }
  // qsto va finito di brutto...

  iter = k;
  zero = (xbeg + xend) / 2.;
  return 0;
}

int Secant (double (*func)(double), double a, double b, double tol, double &zero, int &iter) {
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
  for (k = 0; abs(delta) > tol; k++) { // abs() è indispensabile pké a priori nn hai il controllo di come passeggiano gli estremi e qndi potrebbero tranquillamente invertirsi
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


int Newton (double (*func)(double), double (*func1)(double), double a, double b, double tol, double &zero, int &iter) {
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

  for (k = 0; abs(delta) > tol; k++) {
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


double Func (double x) {
  return sin(x) - ( (x/10.)*(x/10.) + x/5. + 1./3. );
}
