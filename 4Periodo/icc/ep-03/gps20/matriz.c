#include <stdlib.h>
#include <stdio.h>
#include "edo.h"


SL_Tridiag *alocaSisLin(int n){
   SL_Tridiag *SL = malloc(sizeof(SL_Tridiag));
   SL->a = malloc(sizeof(double)*(n));
   SL->d = malloc(sizeof(double)*(n));
   SL->c = malloc(sizeof(double)*(n));
   SL->b = malloc(sizeof(double)*(n));
   SL->n = n;

   return SL;
}

int desalocaSisLin(SL_Tridiag *SL){
   free(SL->a);
   free(SL->b);
   free(SL->c);
   free(SL->d);
   free(SL);
   SL = NULL;

   return (SL == NULL);
}

void imprimeSL(SL_Tridiag *SL){
   for(int i = 0; i < SL->n; i++){
      if(i > 0 && i <= SL->n-2){
         printf("%15g  %15g  %15g | %g\n", SL->a[i-1], SL->d[i], SL->c[i], SL->b[i]);
      }
      else if(i == 0){
         printf("%15d  %15g  %15g | %g\n", 0, SL->d[i], SL->c[i], SL->b[i]);
      }
      else{
         printf("%15g  %15g  %15d | %g\n", SL->a[i], SL->d[i], 0, SL->b[i]);
      }
   }
}

void imprimeVetor(double *x, int n){
   for(int i = 0; i < n; i++){
      printf("%g ", x[i]);
   }
   printf("\n");
}