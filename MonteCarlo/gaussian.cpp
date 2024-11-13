#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ctime>

double Gaussian (double x, double mu, double sigma);

int main() {
  using namespace std;
  srand48(time(NULL));

  double x, y;
  double c;
  double g;

  double mu, sigma;
  ofstream fdata;

  fdata.open("gaussian.dat");

  mu = 0.;
  sigma = 0.5;

  for( int i = 0; i < 1.e5; i++) {
    c = 1.;
    x = (drand48() - .5 ) *5; // random number in range [-5,5]
    y = c * drand48();
    g = Gaussian (x, mu, sigma);

    if (g < y) continue;
    else fdata << x << " " << y << endl;
  }

  fdata.close();

  return 0;
}


double Gaussian (double x, double mu, double sigma) {
  return 1. / ( sqrt(2 * M_PI) * sigma) * exp(- .5 * (x- mu)*(x-mu)/(sigma*sigma));
}
