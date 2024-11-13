#include <iostream>
#include <cmath>
#include <iomanip>

int Bisection (double (*func)(double), double a, double b, double tol, double &zero, int &iter);
int Bracket ( double (*func)(double), double a, double b, int N, double xL[], double xR[]);

double LegPol (double x, int n);
double deLegPol (double x, int n);
double Leg_wrapper (double x);
double deLeg_wrapper (double x);

int N = 2;

// qua nn siamo riusciti a combinare nulla, purtroppo, nel senso che è praticamente scritto ma nn funziona una mazza
// boia
int main () {
  using namespace std;

  double w[N];
  double deLeg;
   
  double tol = 1.e-6;
  int iter = 0;

  int zero_counter;
  double xL[N], xR[N];
  
//cout << LegPol(2, 4) << endl;
  int Nr = N*20 + 3;
  zero_counter = Bracket(Leg_wrapper, -1., 1., Nr, xL, xR);

  double zero[zero_counter];
  double den; // auxiliary for computations

  for (int i=0; i < zero_counter; i++) {
    zero[i] = Bisection(deLeg_wrapper, -1, 1, tol, zero[i], iter);
    cout << "Found zero in: (" << xL[i] << ", " << xR[i] << "); zero at " << zero[i] << endl;
//
//  // Weights computation
//    deLeg = deLegPol(zero[i], N);
//    den = (1 - zero[i]) * (1 - zero[i]) * deleg * deleg;
//    w[i] = 2. / den;
//  cout << "For n = " << N << ":" << endl;
//  cout << i << ". zero at " << zero[i] << "; weight = " << w[i] << endl;
  }
  return 0;
}



double LegPol (double x, int n) {
  double pj, pk, pl;

  pj = 1; // P_0
  pk = x; // P_1

  for (int i=1; i <= n; i++) {
    if ( i == n) break;

    pl = (2*i + 1) * pk - i * pj;
    pl /= (i+1);

    // Update the recursion
      pj = pk;
      pk = pl;
  }

  return pk;
}

double deLegPol (double x, int n) { // this requires the degree of the pol to be defined as a global variable

  double pj, pk, depl;

  pj = LegPol(x, n-1);
  pk = LegPol(x, n);
  depl = x * pk - pj;
  depl *= n;
  depl /= (x*x - 1);

  return depl;
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
  double fbeg, fend;
  double delta = 1; // Relative Error

  xbeg = a;
  xend = b;
  fbeg = func(xbeg);
  fend = func(xend);

  // per ottimizzare mi basta ricordarmi dl valore calcolato dla funz nl'estremo che tengo
  for (k = 0; delta >= tol; k++) {
    xc = (xbeg + xend) * .5;

    if (fbeg*fend < 0) {
      xend = xc;
    }
    else if (fbeg*fend > 0) {
      xbeg = xc;
    }
    else {
      if (fbeg==0) {
        zero = xbeg;
        return 0;
      }
      else if (fend==0) {
        zero = xend;
        return 0;
      }
    }
    delta *= .5;

#if DEBUG == TRUE
    //    cout << "Bisection(): k = " << k << "; [a,b] = [" << xbeg << ", " << xend << "]; xm = " << xc << "; dx = " << delta << "; fm = " << func(xc) << endl;
#endif
  }

  zero = xc;

  return 0;
}

double Leg_wrapper (double x) {
  return LegPol(x, N);
}

double deLeg_wrapper (double x) {
  return deLegPol(x, N);
}
