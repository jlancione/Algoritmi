#include <iostream>
#include <cmath>
#include <cstdlib>

double Average(double*, int);
double Variance(double*, int);
double DevStd(double*, int);

int main(){
  using namespace std;

  srand48(time(NULL)); // Seed random number (ogni volta #o, pké ho usato il time)

  const int n = 10;
  double array[n];

  cout << "Array = [";
  for( int i = 0; i < n; i++){
    array[i] = drand48();

    if( i != n-1 ) cout << array[i] << ", ";
    else cout << array[i] << "]" << endl << endl;
  }


  cout << "Average = " << Average(array, n) << endl;
  cout << "Variance = " << Variance(array, n) << endl;
  cout << "Standard Deviation = " << DevStd(array, n) << endl;

  return 0;
}

double Average(double* arr, int nmisure){
  double sum = 0;

  for(int i = 0; i < nmisure; i++){ sum += arr[i];}

  return (double)sum/nmisure;
}

double Variance(double* arr, int nmisure){
  double mu = Average(arr, nmisure);
  double sq_err_sum = 0;

  for(int i = 0; i < nmisure; i++){
    sq_err_sum += (mu - arr[i]) * (mu - arr[i]);
  }
  return (double)sq_err_sum/nmisure;
}

double DevStd(double* arr, int nmisure){
  return sqrt(Variance(arr, nmisure));
}
