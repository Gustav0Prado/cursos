#include <stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  int x = 0;

  fork () ;
  x++ ;
  sleep (5) ;
  wait (0) ;
  fork () ;
  wait (0) ;
  sleep (5) ;
  x++ ;
  printf ("Valor de x: %d\n", x) ;
}
