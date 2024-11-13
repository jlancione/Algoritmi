#ifndef  MY_INTEGRALS
#define MY_INTEGRALS

int RectangularRule (double (*F)(double), double a, double b, int N, double& sum);
int TrapezoidalRule (double (*F)(double), double a, double b, int N, double& sum);
int SimpsonRule (double (*F)(double), double a, double b, int N, double& sum);
int GaussRule (double (*F)(double), double a, double b, int N, int Ng, double& sum);



// UTILITIES
int sort(double& a, double& b);

#endif // ! MY_INTEGRALS
