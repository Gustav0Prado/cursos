#include <stdio.h>
#include <math.h>

#define erro 1e-10

double func(double a)
{
   return pow(a, 2) - 1;
}

/* x - ( f(x)/f'(x) ) */
double phi(double a)
{
   return ( a - (func(a)/2*a) );
}

double bissecao( double xl, double xu, double f(double a), double epsilon, int *iter )
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
      ++(*iter);
   } while(fabs( (xm_new - xm_old)/(xm_new) )*100 > epsilon);

   return xm_new;
}

double iteracao(double x0, double f(double x), double phi(double x), 
                double epsilon_x, double epsilon_f, int max_iter, int *iter)
{
   double x_new = x0, x_old;
   int crit1, crit2, crit3;

   do
   {
      x_old = x_new;
      x_new = phi(x_old);

      crit1 = fabs(x_new - x_old) < epsilon_x;
      crit2 = fabs(f(x_new)) < epsilon_f;
      crit3 = (*iter == max_iter);
      ++(*iter);
   } while(!crit1 && !crit2 && !crit3);

   return x_new;
}

int main(){
   double xl, xu, x0;
   int iter1 = 1, iter2 = 1;

   printf("Insira o limite esquerdo: ");
   scanf("%lf", &xl);
   printf("Insira o limite direito: ");
   scanf("%lf", &xu);

   printf("Insira o X0: ");
   scanf("%lf", &x0);

   void *f = &func;
   void *p = &phi;

   printf("Por bissecao: \n\tZero em: %g\n", bissecao(xl, xu, f, erro, &iter1));
   printf("\t%d iterações\n", iter1);
   printf("Por iteração: \n\tZero em: %g\n", iteracao(x0, f, p, 1e-10, 1e-10, 100, &iter2));
   printf("\t%d iterações\n", iter2);
}