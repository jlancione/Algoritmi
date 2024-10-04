#include <iostream>

double Sum(double&, double&);

int main(){
  using namespace std;

  double a = 11.2;
  double b = 2.3;
  cout << Sum(a,b) << endl;

  return 0;
}

double Sum(double& x, double& y){ return x + y;}
