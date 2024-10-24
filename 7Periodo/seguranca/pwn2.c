#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char entry[1024];

void myprint(char *str)
{
	write(1, str, strlen(str));
}

int main(int argc, char **argv)
{
	volatile int lookatme;
	char stringonme[64];

	gets(entry);

	lookatme = 0;
	strcpy(stringonme, entry);

	if (lookatme == 0x63616665)
		myprint("Ebaa! Toma tua flag: SECRET{???}\n");
	else
		printf("Não foi dessa vez :(, deu: 0x%08x\n", lookatme);
}
