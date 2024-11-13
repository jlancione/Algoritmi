#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>

int main () {
  using namespace std;
  srand48(time(NULL));

  ofstream fdata;
  fdata.open("pi.dat");

  int N = 4;
  int k = 2; // exponent
  double tol = 1.e-4;
  double err;

  double x, y, d;
  double r = 1.;
  double Asq;

  double my_pi;
  int cnt = 0;

  Asq = 2 * r*r; // QSTO DOVREBBE ESSERE 4 BOIA!
  // poi ci rimane da plottarla con la formula 1 po' + precisa che c'è nle slides

  while(1){
    for (int i = 0; i < N; i++) {
      x = (drand48() - .5) * 2.;
      y = (drand48() - .5) * 2.;
      d = sqrt(x*x + y*y);

      if (d > r) continue;
      cnt++;
    }

    my_pi = Asq * (double)cnt / N;
    fdata << N << " " << err << endl;
    cout << "Trying with N = " << N << " (2^" << k << " )"
         << ": my_pi = " << my_pi << endl;

    err = abs( my_pi / M_PI - 1.); // computing relative error
    if( err < tol) break;
    N *= 2;
    k++; 
  }
  cout << my_pi << endl;
  fdata.close();
  
  return 0;
}


