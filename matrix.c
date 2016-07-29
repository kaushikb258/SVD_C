#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void matrix_mult(int n1, int n2, int n3, double **A, double **B, double **C)
{
 int i, j, k;
 double sum = 0.0;

 for (i = 0; i<n1; i++)
 {
  for (j = 0; j<n3; j++)
  {
   for (k = 0; k<n2; k++)
   {
    sum = sum + A[i][k]*B[k][j];
   }
   C[i][j] = sum;
   sum = 0.0;
  }
 }


}
