#include <iostream>


int main(){
  using namespace std;

  float fone = 1.;
  float fepsilon = 1.;

  while( (fone + fepsilon) != fone){ fepsilon /= (float)10;}

  cout << "Machine precision (single) = " << fepsilon << endl;

  double done = 1.;
  double depsilon = 1.;

  while( (done + depsilon) != done){ depsilon /= (double)10;}

  cout << "Machine precision (double) = " << depsilon << endl;

  return 0;
}
