/*	Tabela padrão do Ex está em 2.in
 * (a) a medida que os numeros aumentam, a distancia entre eles tambem, aumentando de 2 em 2
 * e depois apenas de 4 em 4, 8 em 8, etc, devido a representacao numerica
 * (b) numeros nâo normalizados "inteiros" (1.0, 2.0...) são zerados pois dependem do expoente, números não normalizados próximos de zero também
 * dão saltos de representação, por ex: 1.401298464e-45 -> 2.802596929e-45 -> 4.203895393e-45
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
typedef union
{
	int32_t i;
	float f;
	struct
	{ // Bitfields for exploration. Do not use in production code.
		uint32_t mantissa : 23;
		uint32_t exponent : 8;
		uint32_t sign : 1;
	} parts;
} Float_t;

/*Retorna se num eh infinito ou nao*/
int checaInf(Float_t num){
	return (num.parts.exponent == 255 && num.parts.mantissa == 0);
}

/*Retorna se num eh infinito ou nao*/
int checaNan(Float_t num){
	return (num.parts.exponent == 255 && num.parts.mantissa != 0);
}

/* checa infinito e imprime diferente*/
void printFloat_t( Float_t num )
{
	int inf = checaInf(num);
	int nan = checaNan(num);
	int vexp = (num.parts.exponent == 0) ? -126 : num.parts.exponent-127;

	if(!inf && !nan){
		printf("%1.9e  |   0x%08X  |   %d   |   %3d    |        %4d    | 0x%X\n",
			num.f, num.i,
			num.parts.sign, num.parts.exponent, vexp, num.parts.mantissa);
	}
	/* se eh nan */
	else if(nan){
		printf("    %1.9e          |   0x%08X  |   %d   |   %3d    |        %4d    | 0x%X\n",
			num.f, num.i,
			num.parts.sign, num.parts.exponent, vexp, num.parts.mantissa);
	}
	/* Se eh infinito */
	else{
		if(num.parts.sign == 1){
			printf("Infinito Negativo|   0x%08X  |   %d   |   %3d    |    Infinito!   | 0x%X\n",
				num.i,
				num.parts.sign, vexp, num.parts.mantissa);
		}
		else{
			printf("Infinito Positivo|   0x%08X  |   %d   |   %3d    |    Infinito!   | 0x%X\n",
				num.i,
				num.parts.sign, vexp, num.parts.mantissa);
		}
	}
}

int main()
{
	int tam = 0;
	char line[50];
	Float_t *dados = NULL;

	while ((fgets(line, sizeof line, stdin) != NULL) && (line[0] != '\n')){
		tam++;
		dados = realloc(dados, sizeof(Float_t)*tam);
		dados[tam-1].f = atof(line);
	}
	
	/*adiciona espaco para casos especiais*/
	tam += 6;
	dados = realloc(dados, sizeof(Float_t)*tam);

	/* 1º num não normalizado para comparacao */
	dados[tam-6].parts.exponent = 0;
	dados[tam-6].parts.mantissa = 0x000001;

	/* 2º num não normalizado para comparacao */
	dados[tam-5].parts.exponent = 0;
	dados[tam-5].parts.mantissa = 0x000002;

	/* 3º num não normalizado para comparacao */
	dados[tam-4].parts.exponent = 0;
	dados[tam-4].parts.mantissa = 0x000003;

	/* adiciona +inf */
	dados[tam-3].f = 1.796E308;

	/* adiciona -inf */
	dados[tam-2].f = log10f(0);

	/* adiciona nan */
	dados[tam-1].f = log10f(-1);
	

	printf("  Valor float    | Valor Inteiro | Sinal | Expoente | Valor Expoente | Mantissa\n");
	//printf("-------------------------------------------------------------\n");
	for(int i = 0; i < tam; i++){
		printFloat_t(dados[i]);
	}

	free(dados);
}
