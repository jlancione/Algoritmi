#include <iostream>

int main()
{
  using namespace std;
  // integer inputs
  int a = 4;
  int b = 6;

  cout << "Integer operations, a = " << a << ", b = " << b << ":" << endl;
  cout << "Sum: " << a + b << endl;
  cout << "Subtract: " << a - b << endl;
  cout << "Multiply: " << a * b << endl;
  cout << "Divide: " << (double)a / (double)b << endl;
  cout << endl;

  // float inputs
  float c = 3.3;
  float d = 11.2;

  cout << "Float operations, c = " << c << ", d = " << d << ":" << endl;
  cout << "Sum: " << c + d << endl;
  cout << "Subtract: " << c - d << endl;
  cout << "Multiply: " << c * d << endl;
  cout << "Divide: " << (double)c / (double)d << endl;

  return 0;
}
