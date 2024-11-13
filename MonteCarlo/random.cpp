#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define NATOMS    1000

int main() {
  using namespace std;
  srand48(time(NULL));

  ofstream fdata;
  fdata.open("random.dat");

  int natoms = NATOMS;
  int ndec;
  double lambda = 0.01;
  int dt = 1;
  int tmax = 500;

  int t; // keeps track of time
  int a; // act as a counter over atoms

  for(t = 0; t < tmax; t+=dt) {
    ndec = 0;
    for(a = 0; a < natoms; a++) {
      ndec = (drand48() < lambda? ndec+1: ndec);
    }
    natoms -= ndec;
    fdata << t << " " << natoms << endl;
  }

  fdata << endl << endl;
  
  for(t = 0; t < 500; t+=dt) {
    fdata << t << " " << NATOMS * exp(-lambda * t) << endl;
  }


  
  fdata.close();

  return 0;

}
