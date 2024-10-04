#include <iostream>
#include <cmath>
#include <cstdlib>

#define NSIZE   1000 // così nn occupi spazio in memoria, cosa che faresti con const int
void Average(double[], int, double&, double&, double&);

int main(){
  using namespace std;

  srand48(time(NULL)); // Seed random number (ogni volta #o, pké ho usato il time)

  double x[NSIZE], mu, s2, s;

  for( int i = 0; i < NSIZE; i++){
    x[i] = drand48();
  }

  Average(x, NSIZE, mu, s2, s); 
  cout << "Average = " << mu << endl;
  cout << "Variance = " << s2 << endl;
  cout << "Standard Deviation = " << s << endl;

  return 0;
}

void Average(double arr[], int nmisure, double& mu, double& s2, double& s){
  mu = 0;
  s2 = 0;
  s = 0;

  for(int i = 0; i < nmisure; i++){ mu += arr[i];}
  mu /= (double)nmisure;

  for(int i = 0; i < nmisure; i++){ s2 += (mu - arr[i]) * (mu - arr[i]);}
  s2 /= (double)nmisure;

  s = sqrt(s2);
}
