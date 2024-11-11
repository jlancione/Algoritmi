#include <iostream>
#include <iomanip>
#include <cmath>

void QuadraticStd(double, double, double, double&, double&);
void QuadraticClever(double, double, double, double&, double&);

int main(){
  using namespace std;
  cout << setiosflags(ios::scientific);
  //  qua l'idea è di calcolare il delta solo 1 volta, pké tnt è sempre lo stso, poi in realtà i 2 if sono piuttosto inutili pké il conto da fare è lo stso, devi solo metterci dei valori assolati, poi ci andrebbe il controllo sul delta che sia positivo e l'idea è di farlo funzianore

  double a = 1;
  double x1[] = { 2., 1.e-5, 1.e-12};
  double x2[] = {-3., 1.e8, 1.e12};

  double b, c;
  double x_1, x_2; // to store the computed roots

  for(int i = 0; i < 3; i++){
    b = -( x1[i] + x2[i]);
    c = x1[i] * x2[i];
//  cout << "b = " << b << "; c = " << c << endl;

    QuadraticStd(a, b, c, x_1, x_2);
    cout << "Standard quadratic: x1 = " << x_1 << "; x2 = " << x_2 << ";" << endl;
    QuadraticClever(a, b, c, x_1, x_2);
    cout << "Clever   quadratic: x1 = " << x_1 << "; x2 = " << x_2 << ";" << endl;
    cout << endl;
  }

  return 0;
}


void QuadraticStd(double a, double b, double c, double& x1, double& x2){
  double delta;

  delta = sqrt( b*b - 4* a * c); 
//std::cout << delta << std::endl;

  x1 = (-b + delta) / (2 * a);
  x2 = (-b - delta) / (2 * a);
}

void QuadraticClever(double a, double b, double c, double& x1, double& x2){
  double delta;
  double aux;

  delta = sqrt( b*b - 4* a * c); 
//std::cout << delta << std::endl;
  aux = (abs(b) + delta)* .5;
//std::cout << aux << std::endl;

  x1 = (b < 0? aux / a: - aux /a);
  x2 = (b < 0? c / aux: - c / aux);
}
