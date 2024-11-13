#include <iostream>
#include <cmath>
#include <iomanip>
#include "my_integrals.h"

#define NGAUSS    4  // number of points for subinterval (it's the same for integrations x and y)

double Func2D (double x, double y);
double FFunc1D (double x);
double GFunc1D (double y);

static double g_ycoord;  // = fixed value of y for which we integrate along x
static int g_nint;       // = number of intervals in quadrature function

// l'idea è di integrare prima in x (a y fissato, qndi ci va il wrapper) e poi in y qlo che mi esce
// pké se nn ci sono pb con l'integrazione che è già scritta qlo di cui devo occuparmi è gestirla benino e palleggiarmi bene le y e il dominio

int main() {
  using namespace std;
  cout << setiosflags(ios::scientific);

  double ybeg = -1;
  double yend =  1;
  double sum;
  int counter = 0;
  g_nint = 1;

  cout << M_PI << endl;

  double tol = 1.e-5;
  double err = 1.;
  while( err > tol ) {
    GaussRule (GFunc1D, ybeg, yend, g_nint, NGAUSS, sum); // Integrate in the y direction
    err = abs(sum - M_PI) / M_PI;
    cout << err << endl;
    g_nint += 1;
    counter++;
  }
  cout << "You reached the desired relative accuracy (" << tol << "): " << sum << endl;
  cout << "At iteration number " << counter << endl;
  
  return 0;
}

double GFunc1D (double y) { // Qsta ritorna l'integrale in dx a y fissato (globalmente)

  double sum_x;
  double  xbeg = -1; // Define here the domain
  double  xend =  1;  // Define here the domain
  
  g_ycoord = y; // change the global "y" coordinate, look in FFunc1D(), you see it's fixed 
  GaussRule (FFunc1D, xbeg, xend, g_nint, NGAUSS, sum_x); // integrate in the x-direction for fixed y
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
