#include <iostream>
#include <stdlib.h>

double Average(int)

int main(){
  using namespace std;

  const int n = 10;
  double array[n];

  for( int i = 0; i < n; i++){
    array[i] = drand48();
    cout << array[i] << endl;
  }

  return 0;




}
