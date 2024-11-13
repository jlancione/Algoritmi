#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>


// qsto va sistemato un po', c'è la storia di raddoppiare N ad ogni interaz con N numero di random sample che estraggo e ricorda che devi calcolarti l'errore, per momento 1 rispetto a .5 per mom 2 risp a 1/3
// qua proprio nn ci hai capito niente boia :) si vede benissimo
int main() {
  using namespace std;
  
  srand48(time(NULL));
  double number;
  int nmoment = 2;
  double moment = 0;

  ofstream fdata;
  fdata.open("prn.dat");

  for(int i = 0; i < 1e3; i++) {
    number = drand48()*100;
//  fdata << number << endl;

    for(int j = 0; j < 2; j++) {number_pow *= number;}
    moment += number_pow;
    mdata << moment << endl;
  }

  fdata.close();


  return 0;
}
