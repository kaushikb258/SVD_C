#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "svd.h"
#include "matrix.h"


const int ndof = 300*100*7;
const int isnp = 250;

//------------------------------------


main()
{

 int i, j, k;
 FILE *f;


 double *X;
 X = (double*)malloc(isnp*ndof*sizeof(double));

 printf("reading input file \n");
 
 f = fopen("snapshot_u1", "r");
 k = -1;
 for (j=0; j<isnp; j++)
 {
  for (i=0; i<ndof; i++)
  {
   k++;
   fscanf(f,"%lf \n",&X[k]);
  }
 }
 fclose(f); 

 printf("finished reading input file \n");


 double **A;
 int row;

 // allocate an "array of arrays" of int
 A = (double**)malloc( ndof* sizeof(double*) ) ;
  
  for(row = 0; row < ndof; row++ )
  {
    A[row] = (double*)malloc( isnp*sizeof(double) ) ;
  }
 

 
 
 k = -1;
 for (i=0; i<ndof; i++)
 {
  for (j=0; j<isnp; j++)
  {
   k++;
   A[i][j] = X[k];
  }
 }

 free(X);

 
 double *w;
 w = (double*)malloc( isnp* sizeof(double*) ) ; 

 double **v;
 v = (double**)malloc( isnp* sizeof(double*) ) ;

  for(row = 0; row < isnp; row++ )
  {
    v[row] = (double*)malloc( isnp*sizeof(double) ) ;
  }
 

 dsvd(A,ndof,isnp,w,v);
  
 printf("done with svd \n");


 
 f = fopen ("w.dat", "w+");
 for (i=0; i<isnp; i++)
 {
  fprintf(f, "%d %f\n", i,w[i]);
 }
 fclose(f);

//--------------------------------
// check for orthonormality

 double **AT;
 
 // allocate an "array of arrays" of int
 AT = (double**)malloc( isnp* sizeof(double*) ) ;
  
  for(row = 0; row < isnp; row++ )
  {
    AT[row] = (double*)malloc( ndof*sizeof(double) ) ;
  }


 for (i=0; i<ndof; i++)
 {
  for (j=0; j<isnp; j++)
  {
   AT[j][i] = A[i][j];
  }
 }

 
 double **Iden;
 
 // allocate an "array of arrays" of int
 Iden = (double**)malloc( isnp* sizeof(double*) ) ;
  
  for(row = 0; row < isnp; row++ )
  {
    Iden[row] = (double*)malloc( isnp*sizeof(double) ) ;
  }



 matrix_mult(isnp,ndof,isnp,AT,A,Iden);


 printf("Identity matrix? \n");

 double s1 = 0.0;
 double s2 = 0.0; 

 for (i=0; i<isnp; i++)
 {
  for (j=0; j<isnp; j++)
  {
   if(i == j) s1 += Iden[i][j];
   else s2 += Iden[i][j];
  }
 }

 s1 /= (double)(isnp);
 s2 /= (double)(isnp*(isnp-1));

 printf("sum of diagonals = %f \n", s1);
 printf("sum of off-diagonals = %f \n", s2);
//------------------------------------



}
