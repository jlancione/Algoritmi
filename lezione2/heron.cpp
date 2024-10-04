#include <iostream>
#include <iomanip>
#include <cmath>

void heron(double&, double, double&);

int main(){
  using namespace std;
  cout << setiosflags(ios::scientific);
  double number, guess;
  
  cout << "Enter a real number:" << endl;
  cin >> number;
  cout << "Enter your guess: " << endl;
  cin >> guess;

  cout << "----------------------------" << endl;

  double err = 1 - guess / sqrt(number);

  for(int i = 1; err > 1e-9; i++){
    heron(guess, number, err);
    cout << "Iteration # " << i << ": x = "
         << setw(22)
         << setprecision(14)
         << guess << "; "
         << "err = " << err << endl;
  }
  cout << endl;
  cout << "The correct sqrt is: " << sqrt(number) << endl;
  cout << "The approximation is:" << guess << endl;

  return 0;
}

void heron(double& x, double S, double& error){
    x = .5 * (x + S / x);
    error = fabs(1 - x / sqrt(S));
}
