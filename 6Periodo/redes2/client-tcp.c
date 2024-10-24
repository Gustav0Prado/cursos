#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
   int sock_descr;
   int num_bytes;
   struct sockaddr_in sa;
   struct hostent *hp;
   char buf[BUFSIZ+1];
   char *host;
   char *dados;

   if(argc != 4) {
      puts("Uso correto: ./clien-tcp <servidor> <porta> <dados>\n");
      exit(1);
   }

   host = argv[1];
   dados = argv[3];
   if(!(hp = gethostbyname(host))) {
      puts("DNS não achou servidor\n");
      exit(1);
   }
   bcopy((char*)hp->h_addr_list[0], (char *)&sa.sin_addr, hp->h_length);
   sa.sin_family = AF_INET;
   sa.sin_port = htons(atoi(argv[2]));
   sock_descr = socket(AF_INET, SOCK_STREAM, 0);
   if(connect(sock_descr, &sa, sizeof(sa) < 0)) {
      puts("Não consegui conectar com server\n");
      exit(1);
   }
   if(write(sock_descr, dados, strlen(dados)) != strlen(dados)) {
      puts("Não consegui transmitir os dados\n");
      exit(1);
   }
   memset(buf, 0, BUFSIZ);
   read(sock_descr, buf, BUFSIZ);
   printf("Sou cliente recebi: %s\n", buf);
   close(sock_descr);

   return (0);
}