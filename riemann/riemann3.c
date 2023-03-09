#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define A 1
#define B 40
#define N 10e6

double f(double x);
double trapezoids(double a, double b, int n);

int main(int argc, char* argv[]) {
  double integral;
  double a=A, b=B;
  int n;

  if(argc > 1) {
    a = strtol(argv[1], NULL, 10);
    b = strtol(argv[2], NULL, 10);
    n = strtol(argv[3], NULL, 10);
  }

  integral = trapezoids(a,b,n);
  printf("With n = %d trapezoids, our approximation \n",n);
  printf("of the integral from %f to %f is = %.10f\n", a,b,integral);
  return 0;
}

double trapezoids(double a, double b, int n) {
  double integral, h, x, local_sum;
  double local_a, local_b;
  int i, local_n, k;
  h = (b-a)/n;
  integral = (f(a) + f(b)) / 2.0;
  
  #pragma omp parallel for private(local_sum, local_a, local_b, local_n, i) reduction(+: integral)
  for(k = 1; k <= n-1; k++) {
    int thread_ID = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    local_n = n/thread_count;
    local_a = a + thread_ID*local_n*h;
    local_b = local_a + local_n*h;
    printf("\nThread %d: Local n = %d, local a = %f, local b = %f \n", thread_ID, local_n, local_a, local_b);
    local_sum = 0.0;
    for(i = 1; i <= local_n; i++) {
      x = local_a + i*h;
      local_sum += f(x);
    }
    integral += local_sum;
  }
  
  integral = integral * h;
  return integral;
}

double f(double x) {
  double return_val;
  return_val = x*x;
  return return_val;
}