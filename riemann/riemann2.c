#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define A 1
#define B 40
#define N 10e6

double f(double x);
double trapezoides(double a, double b, int n);

int main(int argc, char* argv[]) {
  double integral;
  double a=A, b=B;
  int n;
  double h;

  if(argc > 1) {
    a = strtol(argv[1], NULL, 10);
    b = strtol(argv[2], NULL, 10);
    n = strtol(argv[3], NULL, 10);
  }

  integral = trapezoides(a,b,n);
  printf("Con n = %d trapezoides, nuestra aproximacion \n",n);
  printf("de la integral de %f a %f es = %.10f\n", a,b,integral);
  return 0;
}

double trapezoides(double a, double b, int n) {
  double integral, h;
  int k;
  h = (b-a)/n;
  integral = (f(a) + f(b)) / 2.0;

  #pragma omp parallel for reduction(+: integral)
  for(k = 1; k <= n-1; k++) {
    integral += f(a + k*h);
  }

  integral = integral * h;
  return integral;
}

double f(double x) {
  double return_val;
  return_val = x*x;
  return return_val;
}
