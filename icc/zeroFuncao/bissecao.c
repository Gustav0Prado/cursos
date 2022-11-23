#include <stdio.h>
#include <math.h>

#define erro 1e-10

double func(double a)
{
   return pow(a, 3) + pow(a, 2) - a + 5;
}

double bissecao( double xl, double xu, double f(double a), double epsilon )
{
   double xm_new, xm_old;

   xm_new = (xl + xu) / 2;
   if(f(xl)*f(xm_new) < 0){
      xu = xm_new;
   }
   else if(f(xl)*f(xm_new) > 0){
      xl = xm_new;
   }
   else{
      return xm_new;
   }

   do{
      xm_old = xm_new;
      xm_new = (xl + xu) / 2;
      if(f(xl)*f(xm_new) < 0){
         xu = xm_new;
      }
      else if(f(xl)*f(xm_new) > 0){
         xl = xm_new;
      }
      else{
         return xm_new;
      }
   } while(fabs( (xm_new - xm_old)/(xm_new) )*100 > epsilon);

   return xm_new;
}

int main(){
   double xl, xu;

   printf("Insira o limite esquerdo: ");
   scanf("%lf", &xl);
   printf("Insira o limite direito: ");
   scanf("%lf", &xu);

   void *f = &func;

   printf("Zero em: %g\n", bissecao(xl, xu, f, erro));
}