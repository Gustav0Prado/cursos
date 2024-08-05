#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define RED           "\e[1;31m"
#define GREEN         "\e[1;32m"
#define YELLOW        "\e[1;33m"
#define BLUE          "\e[1;34m"
#define MAGENTA       "\e[1;35m"
#define CYAN          "\e[1;36m"
#define LIGHT_GRAY    "\e[1;37m"
#define RESET         "\e[0m"
#define SIZE 32

#define MOVE_UP(n) printf("\033[%dA", (n))
#define MOVE_DOWN(n) printf("\033[%dB", (n))
#define MOVE_RIGHT(n) printf("\033[%dC", (n))
#define MOVE_LEFT(n) printf("\033[%dD", (n))

void error(char *msg)
{
	printf("\n%s[-] %s%s\n", RED, msg, BLUE);
}

void cls(void)
{
	printf("\033[2J");
	printf("\033[%d;%dH", 0, 0);
}

void delulu(void)
{
	char c;
	int fp = open("./flag.txt", O_RDONLY);
	if (fp < 0) {
		perror("\nErro ao abrir flag.txt. Por favor, contate um Admin.\n");
		exit(EXIT_FAILURE);
	}

	printf("Você conseguiu enganar o robô, aqui está sua nova identidade: ");
	while ( read(fp, &c, 1) > 0 )
		fprintf(stdout, "%c", c);
	close(fp);
}

void banner(void)
{
	char *ban =
""
"      🟩🟩🟩🟩🟩\n"
"    🟩🟩⬛️⬛️🟩🟩\n"
"  🟩🟩⬛️⬜️⬛️🟩🟩\n"
"🟩🟩⬛️⬜️⬜️⬛️🟩🟩\n"
"🟩🟩⬛️⬜️⬜️⬛️🟩🟩\n"
"🟩🟩🟩🟩⬛️🟩🟩🟩\n"
"🟩🟩⬛️⬛️⬛️⬛️🟩🟩\n"
"  🟩🟩🟩🟩🟩🟩🟩\n"
"🟩🟩🟩🟩🟩🟩🟩🟩🟩\n"
"    🟩🟩⬛️⬛️🟩🟩\n"
"      🟩⬛️⬛️🟩\n"
"        🟩🟩🟩\n"
"          🟩\n"
"          🟩\n";

	printf("%s\nO robô de identificação facial do SECRET irá escanear você em breve!\n\nTente enganá-lo mudando sua identidade.\n\n>> ", ban);
}

int main(void)
{
	unsigned long int target = 0x1337babe; 
	unsigned long int *tp = &target;
	char buf[0x20] = {0};

	read(0, buf, 0x20-1);

	printf("\n[!] Verificando... ");
	printf(buf);
	printf("\ntarget:  0x%x\n&target: %p\n", target, tp);

	target != 0x1337beef ? error("ALERT ALERT ALERT ALERT\n") : delulu();

	return 0;
}

__attribute__((constructor))
void setup(void)
{
	cls();
	banner();
	setvbuf(stdin,  NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	alarm(0x1312);	
}
