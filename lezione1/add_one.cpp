#include <iostream>

double add_one(double&);

int main(){
  using namespace std;

  double a = 11.2;
  cout << "Add one to " << a << ": " << add_one(a) << endl;
  return 0;
}

double add_one(double& x){ return x + 1;}
