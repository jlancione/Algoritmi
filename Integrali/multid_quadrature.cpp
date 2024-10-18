#include <iostream>
#include <cmath>
#include <iomanip>

double Func2D (double x, double y);
double FFunc1D (double x);
double GFunc1D (double y);

double GaussQuad (double (*F)(double), double a, double b, int N, int Ng);

static double g_ycoord;  // = fixed value of y for which we integrate along x
static int g_nint;       // = number of intervals in quadrature function

// l'idea è di integrare prima in x (a y fissato, qndi ci va il wrapper) e poi in y qlo che mi esce
// devo qndi fare un po' occhio ai domini (ma qsto + avanti)
// qndi in qlche modo bisognerà aggiornare le variabili globali
// pké se nn ci sono pb con l'integrazione che è già scritta qlo di cui devo occuparmi è gestirla benino e palleggiarmi bene le y e il dominio

int main() {
  using namespace std;

  double ybeg = -1;
  double yend =  1;
  double sum;
  g_nint = 1;

  sum = GaussQuad (GFunc1D, ybeg, yend, g_nint, 4); // Integrate in the y direction

  cout << sum << endl;
  return 0;
}


double GFunc1D (double y) { // Qsta ritorna l'integrale in dx a y fissato

  double sum_x;
  double  xbeg = -1; // Define here the domain
  double  xend =  1;  // Define here the domain
  
  g_ycoord = y; // change the global "y" coordinate
  sum_x = GaussQuad (FFunc1D, xbeg, xend, g_nint, 4); // integrate in the x-direction for fixed y
  return sum_x;
}

double FFunc1D (double x) { // This is a wrapper
  return Func2D (x, g_ycoord);
}

double Func2D (double x, double y) { // This is the actual 2D function
//double x2 = x*x; double y2 = y*y;
//return x2*x2 * y2 + 2 * x2*y2 - y* x2 + 2;
  double r = sqrt( x*x + y*y);

  return (r <= 1? 1.: 0.);
}



// Questo poi andrà levato nn appena scriviamo per bene la libreria e ci basterà importare quella
double GaussQuad (double (*F)(double), double a, double b, int N, int Ng) {
  /////////////////////////////
  /// a, b are the extremes of the intervals; N is the number of subintervals; Ng is the number of gaussian points per subinterval
  /////////////////////////////

  double w[32]; double t[32];    // both initialized statically, we have a maximum capacity for the function

  if (Ng == 1) {
    t[0] =           0. ; w[0] = 2.;
  }
  else if (Ng == 2) {
    t[0] = sqrt(1. / 3.); w[0] = 1.;
    t[1] = - t[0];        w[1] = w[0];

  }
  else if (Ng == 3) {
    t[0] =           0  ; w[0] = 8. / 9.;
    t[1] = sqrt(3. / 5.); w[1] = 5. / 9.;
    t[2] = - t[1];        w[2] = w[1];
  }
  else if (Ng == 4) { // fatti poi 4 5 6 a casa
    t[0] = sqrt( (3. - 2. * sqrt(6. / 5.)) / 7.); w[0] = (18 + sqrt(30) )/ 36.;
    t[1] = -t[0]                                ; w[1] = w[0];
    t[2] = sqrt( (3. + 2. * sqrt(6. / 5.)) / 7.); w[2] = (18 - sqrt(30) )/ 36.;
    t[3] = -t[2]                                ; w[3] = w[2];
  }
  else {
    std::cout << "! GaussQuad NOT defined for ngauss = " << Ng << std::endl;
    exit(1);
  }

  double sum;
  double x;      // evaluation point for f
  double x0;
  double x1 = a; // to inizialize correctly x1 and x0 in the first subinterval
  double xsum;   // for optimization in the loops

  double dx = (double)(b - a) / (double)N;

  sum = 0.0;
  for(int j = 0; j < N; j++) {       // loop over subintervals
    x0 = x1;
    x1 = a + dx * (j + 1);
    xsum = x0 + x1;

    for(int i = 0; i < Ng; i++) {    // Apply gaussian rule
      x = dx * t[i] + xsum;
      x /= 2.;
      sum += F(x) * w[i];
    }
  }

  sum *= ( b - a) / 2.;

  return sum;

}

