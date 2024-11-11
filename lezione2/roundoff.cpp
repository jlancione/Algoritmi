#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
  using namespace std;

  cout << setiosflags(ios::scientific);

  float x = 1e4;
  cout << "Example #1: compute sqrt(x^2 + 1) - x for large x" << endl;
  cout << "=================================================" << endl;
  for(int i = 0; i < 7; i++){
    cout << "x = " << x << "; ";
    cout << "f (original)     = " << sqrt( x*x + 1) - x << "; ";
    cout << "f (rationalized) = " << (float)1. / ( sqrt( x*x + 1) + x ) << "; ";
    cout << "f(taylor) = " << (float).5 / x << endl; 
    x *= 10;
  }
  cout << endl;

  x = 1e-1;
  cout << "Example #2: compute 1 - cos(x) for small x" << endl;
  cout << "=================================================" << endl;
  for(int i = 0; i < 7; i++){
    cout << "x = " << x << "; ";
    cout << "f (orginal)      = " << 1 - cos(x) << "; ";
    cout << "f (rationalized) = " << sin(x) * sin(x) / ( 1 + cos(x) )<< "; ";
    cout << "f(taylor) = " << .5 * x*x << endl; 
    x /= 10;
  }


  return 0;
}
