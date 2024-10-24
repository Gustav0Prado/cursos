/* Caso padrão do Ex está em 3.in */
#include <stdio.h>
#include <math.h>

/* usa 10^-15 como erro maximo */
#define ERRO 1e-15

void printIntervalo(float a, float b){
	/* calcula se a > b */
	if((a-b) > ERRO){
		/*printa b depois a*/
		printf("[%f, %f]\n", b, a);
	}
	else{
		/*printa a depois b*/
		printf("[%f, %f]\n", a, b);
	}
}

/* powf nao aceita base negativa (resultado eh sempre nan), entao invertemos o sinal da base e do resultado */
float powN(float a, float b){
	if(a < ERRO){
		return -(powf(-a, b));
	}
	else{
		return powf(a, b);
	}
}

int main(){
	float A;
	float B;
	float errA;
	float errB;

	printf("Insira A: ");
	scanf("%f", &A);
	printf("Insira B: ");
	scanf("%f", &B);
	printf("Insira o erro sobre A: ");
	scanf("%f", &errA);
	printf("Insira o erro sobre B: ");
	scanf("%f", &errB);

	/* Utiliza os numeros e erros para calcular os intervalos de resposta das operações */

	printf("\nA+B = ");
	printIntervalo((A-errA)+(B-errB), (A+errA)+(B+errB));
	printf("A/B = ");
	printIntervalo((A-errA)/(B-errB), (A+errA)/(B+errB));
	printf("A*B = ");
	printIntervalo((A-errA)*(B-errB), (A+errA)*(B+errB));
	printf("A^B = ");
	printIntervalo(powN((A-errA),(B-errB)), powN((A+errA),(B+errB)));
}