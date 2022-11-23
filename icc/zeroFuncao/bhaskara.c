#include <stdio.h>
#include <math.h>

void bhaskara(double a, double b, double c, double *x1, double *x2)
{
   double d = b*b - 4*a*c;
   *x1 = (-b+sqrt(d))/(2*a);
   *x2 = (-b-sqrt(d))/(2*a);
}

int sinal(double a){
   return (a < 0) ? -1 : 1; 
}

void bhaskaraOpt(double a, double b, double c, double *x1, double *x2)
{
   double d = b*b - 4*a*c;
   *x1 = (-b-sinal(b)*sqrt(d))/(2*a);
   *x2 = c/(a*(*x1));
}

int main(){
   z, c, x1, x2, x3, x4;

   // printf("Insira o A: ");
   // scanf("%lf", &a);
   // printf("Insira o B: ");
   // scanf("%lf", &b);
   // printf("Insira o C: ");
   // scanf("%lf", &c);

   a = 0.0005;
   b = 100;
   c = 0.005;

   bhaskara(a, b, c, &x1, &x2);
   bhaskaraOpt(a, b, c, &x3, &x4);

   printf("Bhaskara normal:\n");
   printf("\tX1: %g\n", x1);
   printf("\tX2: %g\n", x2);

   printf("Bhaskara otimizado:\n");
   printf("\tX1: %g\n", x3);
   printf("\tX2: %g\n", x4);
}