#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double x){
   return 4*x*x*x + 5*x*x + 15;
}

int main(){
   //Monte Carlo para 1 variavel
   int n = 100000;
   double a, b, x, y, res, h, soma;

   // printf("Insira a quantidade de amostras: ");
   // scanf("%d", &n);

   printf("Insira o limite inferior: ");
   scanf("%lg", &a);

   printf("Insira o limite superior: ");
   scanf("%lg", &b);

   printf("\n");

   //Método dos retangulos (Riemann)
   h = (b-a)/n;
   soma = 0.0;
   for(int i = 0; i < n; ++i){
      //E ( f(xi) )
      soma += f(a+h*i)*h;
   }
   printf("* Retangulos  = %.7g\n", soma);


   //Metodo dos trapezios
   h = (b-a)/n;
   soma = 0.0;
   for(int i = 0; i < n; ++i){
      //E ( f(xi) + f(x(i+1)) )
      soma += f(a+h*i) + f(a+h*(i+1));
   }
   res = (h * soma)/2;
   printf("* Trapezios   = %.7g\n", res);


   //Metodo de Simpson
   h = (b-a)/n;
   soma = 0.0;
   for(int i = 0; i < n-1; i+=2){
      //E ( f(xi) + 4f(x(i+1)) + f(x(i+2)) )
      soma += f(a+h*i) + 4*f(a+h*(i+1)) + f(a+h*(i+2));
   }
   res = (h * soma)/3;
   printf("* Simpson     = %.7g\n", res);


   //Metodo de Monte Carlo
   soma = 0.0;
   for(int i = 0; i < n; ++i){
      x = a + ((double)random() / RAND_MAX) * (b-a);
      soma += f(x);
   }
   res = (soma/n) * (b-a);
   printf("* Monte Carlo = %.7g\n", res);
}