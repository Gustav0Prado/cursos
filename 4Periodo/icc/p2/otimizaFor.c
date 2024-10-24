#include <stdio.h>

int main(){
   int x = 10;

   for(int i = 0; i < 5; ++i){
      if(x == 1){
         printf("A: %d\n", i);
      }
      else if(x == 2){
         printf("B: %d\n", i);
      }
      else{
         printf("C: %d\n", i);
      }
   }

   printf("\n");

   for(int i = 0; i < 5 && (x == 1); ++i){
      printf("A: %d\n", i);
   }
   for(int i = 0; i < 5 && (x == 2); ++i){
      printf("B: %d\n", i);
   }
   for(int i = 0; i < 5 && (x != 1 && x != 2); ++i){
      printf("C: %d\n", i);
   }
   printf("\n");

   if(x == 1){
      for(int i = 0; i < 5; ++i){
         printf("A: %d\n", i);
      }
   }
   else if(x == 2){
      for(int i = 0; i < 5; ++i){
         printf("B: %d\n", i);
      }
   }
   else{
      for(int i = 0; i < 5; ++i){
         printf("C: %d\n", i);
      }
   }
}