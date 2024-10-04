#include <iostream>

void QuadraticStd(float, float, float, float&, float&);
void QuadraticClever(float, float, float, float&, float&);

int main(){
  using namespace std;

//  cout << setiosflags::ios
  //  qua l'idea è di calcolare il delta solo 1 volta, pké tnt è sempre lo stso, poi in realtà i 2 if sono piuttosto inutili pké il conto da fare è lo stso, devi solo metterci dei valori assolati, poi ci andrebbe il controllo sul delta che sia positivo e l'idea è di farlo funzianore

  float a = 1;
  float x1[] = {2, 10e-5, 10e-12};
  float x2[] = {-3, 10e8, 10e12};

  for(int i = 0; i < 3; i++){
    int x11
  }

}


void QuadraticStd(float a, float b, float c, float& x1, float& x2){
  x1 = (-b + sqrt( b*b - 4 * a * c )) / (2 * a);
  x2 = (-b - sqrt( b*b - 4 * a * c )) / (2 * a);
}

void QuadraticClever(float a, float b, float c, float& x1, float& x2){
  if( b >= 0 ){
    x1 = (-b - sqrt( b*b - 4 * a * c )) / (2 * a);
    x2 = (2 * c) / (-b - sqrt( b*b - 4 * a * c ));
  }
  if( b < 0 ){
    x1 = (2 * c) / (-b + sqrt( b*b - 4 * a * c ));
    x2 = (-b + sqrt( b*b - 4 * a * c )) / (2 * a);
  }
}
