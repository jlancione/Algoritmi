#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
  using namespace std;

  srand(time(NULL));
  int guess;
  int number;
  int x0, x1;

  x0 = 0;
  x1 = 100;
  number = rand()%100 + 1;
  
  int i = 1; // counter

  while(1){
    cout << "Type your guess in [" << x0 << ", " << x1 << "] > ";
    cin >> guess;
    if (guess == number) {
      cout << "Number found in " << i << " tries!" << endl;
      exit(0);
    }
    if (guess >= x1 || guess <= x0) {
      cout << "Guess out of range, you just wasted a try!" << endl; // per qlche ragione qsto viene eseguito sempre...
    }

    x1 = (guess > number && guess < x1? guess: x1);
    x0 = (guess < number && guess > x0? guess: x0);
    i++;
  }

  return 0;
}
