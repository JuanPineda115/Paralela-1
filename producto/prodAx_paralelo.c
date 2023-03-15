

   printf("Ingrese las dimensiones m y n de la matriz: ");
   scanf("%d %d",&m,&n);

   //---- Asignación de memoria para la matriz A ----
   if ( (A=(double *)malloc(m*n*sizeof(double))) == NULL )
    perror("memory allocation for A");

   //---- Asignación de memoria para el vector x ----
   if ( (x=(double *)malloc(n*sizeof(double))) == NULL )
    perror("memory allocation for x");

   //---- Asignación de memoria para el vector b ----
   if ( (b=(double *)malloc(m*sizeof(double))) == NULL )
    perror("memory allocation for b");

  printf("Initializing matrix A and vector x\n");

  //---- Inicialización con elementos aleatorios entre 1-7 y 1-13
  for (j=0; j<n; j++)
    x[j] = rand()%7+1;

  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      A[i*n+j] = rand()%13+1;

  printf("Calculando el producto Ax para m = %d n = %d\n",m,n);
  clock_t t;
  t = clock();
  (void) prodAx(m, n, A, x, b);
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

  printf("\nb: \n");
  for(j=0; j<n; j++)
    printf("\t%0.0f ",b[j]);
  printf("\n\n");

  free(A);free(x);free(b);
  printf("prodAx() took %f seconds to execute \n", time_taken);

  return(0);
 }

/* ------------------------
 * prodAx
 * ------------------------
 */
void prodAx(int m, int n, double* A, double* x, double* b) {
  int i, j;

  #pragma omp parallel for shared(m,n,A,x,b) private(i,j)
  for(i = 0; i < m; i++) {
    b[i] = 0.0;  //inicialización elemento i del vec.
    for(j = 0; j < n; j++) {
      b[i] += A[i*n + j] * x[j]; //producto punto
    }
  }/*−−-Fin de parallel for−−−*/
}
