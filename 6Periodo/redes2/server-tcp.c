#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TAMFILA      5
#define MAXHOSTNAME 30

int main(int argc, char *argv[]) {
   int sock_escuta, sock_atende;
   char buffer[BUFSIZ+1];
   struct sockaddr_in sa, isa;
   struct hostent *hp;
   char localhost[MAXHOSTNAME];

   if(argc != 2) {
      puts("Uso correto: ./servidor-tcp <porta>");
      exit(-1);
   }

   gethostname(localhost, MAXHOSTNAME);
   if (! (hp = gethostbyname(localhost) )) {
      puts("Erro ao traduzir DNS => IP\n");
      exit(-1);
   }

   bcopy ((char *) hp->h_addr_list[0], (char *) &sa.sin_addr, hp->h_length);
   sa.sin_port = htons(atoi(argv[1]));
   sa.sin_family = hp->h_addrtype;
   if ((sock_escuta = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      puts ( "Nao consegui abrir o socket" );
		exit (1);
   }
   if( (bind(sock_escuta, (struct sockaddr*)&sa, sizeof(sa)) ) < 0) {
      puts("Não conseguiu fazer bind na porta\n");
      exit(-1);
   }

   listen(sock_escuta, TAMFILA);
   while(1) {
      int i = sizeof(sa);
      sock_atende = accept(sock_escuta, (struct sockaddr*)&isa, (socklen_t *)&i);
      memset(buffer, 0, BUFSIZ);
      read(sock_atende, buffer, BUFSIZ);
      printf("Sou servidor recebi %s\n", buffer);
      write(sock_atende, buffer, BUFSIZ);
      close(sock_atende);
   }

   return 0;
}