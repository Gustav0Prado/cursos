#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "socket.h"

int main(){
   int papel;
   unsigned char msg[256];

   int socket = ConexaoRawSocket("lo");

   printf("0 - Cliente\n1 - Servidor\n");
   scanf("%d", &papel);

   if(papel){
      while(1){
         if(recv(socket, msg, sizeof(msg), 0) >= 0){
            printf("%s\n", msg);
         }
      }
   }
   else{
      strncpy(msg, "Hello, World!", 15);
      send(socket, msg, sizeof(msg), 0);
   }
}
