#include <iostream>


int main(){
  using namespace std;

  float one_float = 1.;
  float epsilon = 1.;

  while( (one_float + epsilon) != one_float){ epsilon /= (float)10;}

  cout << "Machine precision (single) = " << epsilon << endl;

  double one_double = 1.;

  epsilon = 1.;

  while( (one_double + epsilon) != one_double){ epsilon /= (double)10;}

  cout << "Machine precision (double) = " << epsilon << endl;

  return 0;
}
