#include <iostream>

int Intdivision( int&, int&, int&, int& );

int main(){
  using namespace std;
  
  int a = 10;
  int b = 3;
  int q, r;

  int flag;

  flag = Intdivision( a, b, q, r );

  if(flag != 0 ) return 1; // per gestire gli errori dal main (altrimenti si può fare dl'interno dla funzione)

  cout << "Integer division between a = " << a << " and b = " << b << ":" << endl;
  cout << "Quotient:" << q << endl;
  cout << "Remainder: " << r << endl;
  return 0;
}

int Intdivision( int& a, int& b, int& q, int& r ){ 
  if( b == 0 ) return 1; // Means failure
  q = a / b;
  r = a % b;
  return 0; // Means success
}

