#include <stdio.h>
#include <string.h>

void myprint(char *str)
{
	write(1, str, strlen(str));
}

void echo()
{
	int accessGranted = 0;
	char buffer[30];

	myprint("Digite algo: ");
	gets(buffer);

	if (accessGranted)
		myprint("SECRET{???}\n");
	else
		myprint("Acesso negado.\n");
}

int main()
{
	echo();

	return 0;
}
