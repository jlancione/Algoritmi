#include <iostream>
#include <cmath>
#include <iomanip>


double RectangularRule (double (*F)(double), double a, double b, int N); // vogliamo 1 cosa pratica da usare nel main, la chiamo e ho subito l'integrale
double TrapezoidalRule (double (*F)(double), double a, double b, int N);
double SimpsonRule (double (*F)(double), double a, double b, int N);

double func(double);


int main(){
  using namespace std;
  cout << setiosflags(ios::scientific);

  double tol = 1e-5;
  double int_old, int_new; 

  cout << setw(14) << "Exact: " << setw(22) << setprecision(14) << 1 - 1./exp(1) << endl;

  int n = 4;
  int_old = RectangularRule(func, 0, 1, n);
  for(int i=0; abs(int_new - int_old) > tol; i++){
    int_old = (i==0 ? : int_new);
    n *= 2;
    int_new = RectangularRule(func, 0, 1, n);
    }

  cout << setw(14) << "Rectangular: " << setw(22) << setprecision(14)
    << int_new << "    (N = " << n << ")" << endl;

  n = 4;
  int_old = TrapezoidalRule(func, 0, 1, n);
  for(int i=0; abs(int_new - int_old) > tol; i++){
    int_old = (i==0 ? : int_new);
    n *= 2;
    int_new = TrapezoidalRule(func, 0, 1, n);
    }

  cout << setw(14) << "Trapezoidal: " << setw(22) << setprecision(14)
    << int_new << "    (N = " << n << ")" << endl;

  n = 4;
  int_old = SimpsonRule(func, 0, 1, n);
  for(int i=0; abs(int_new - int_old) > tol; i++){
    int_old = (i==0 ? : int_new);
    n *= 2;
    int_new = SimpsonRule(func, 0, 1, n);
    }

  cout << setw(14) << "Simpson: " << setw(22) << setprecision(14)
    << int_new << "    (N = " << n << ")" << endl;

  return 0;
}


double RectangularRule (double (*F)(double), double a, double b, int N){ // N è il numero di intervalli
  double h = ( b - a)/(double)N;
  double sum = 0;
  for(int i=0; i<N; i++){
   sum += F(a + h*i); 
  }
  sum *= h;
  return sum;
}

double TrapezoidalRule (double (*F)(double), double a, double b, int N){ // N è il numero di intervalli
  double h = ( b - a)/(double)N;
  double sum = 0;

  sum += ( F(a) + F(b)) / (double) 2;
  for(int i=1; i < N; i++){
   sum += F(a + h*i); 
  }
  sum *= h;
  return sum;
}

double SimpsonRule (double (*F)(double), double a, double b, int N){
  // Note: n must be even

  double h = ( b - a) / (double)N;
  double sum = 0;

  // Opzione 1 con l'if
//for(int i=1; i < N; i++){
//  if(i % 2 == 1) sum += F(a + h*i) * 2;  // gli if nn ci piacciono
//  else sum += F(a + h*i);
//}
//sum *= 2;

  // Opzione 2 con il doppio for
//for(int i=1; i < N; i+=2){                
//  sum += F(a + h*i) * 2;  
//}                                        
//for(int i=2; i < N; i+=2){                
//  sum += F(a + h*i);  
//}                                        
//sum *= 2;

  // Opzione 3, the pro way
  double w = 4.0;

  for(int i=1; i < N; i++){                
    sum += F(a + h*i) * w;  
    w = 6.0 - w;
  }

  sum += F(a) + F(b);
  sum *= h;
  sum /= (double) 3;
  return sum;

}

double func(double x){
  return exp(-x);
}
