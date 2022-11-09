/*
 * (a) somaSequencia: acumula os valores de todos os elementos de um vetor de float linearmente, da última posição até a primeira
 * 	 somaPares: acumula os valores de todos os elementos de um vetor dividindo-os em pares, e somando numeros com magnitude semelhante
 *
 * (b) devido ao erro acumulado em operações consecutivas e cancelamento subtrativo (numero grande + numero muito pequeno) repetidas vezes, somaSequencia causa
 * 	uma falta de precisão no resultado final, o que não ocorre com somaPar, por não ser sequencial
 *
 * (c)  comparação somaSequencia-somaPar
 * 	 *1X:  diferenca de +0.584472656250000
 * 	 *10x: diferença de +55.8046875
 * 	 *100x: diferença de -906.265
 * 	 *1000x: diferença de -601295
 * 
 * 	como dito anteriormente, somaSequencia, ao realizar operações sequencias e continuas, causa perda de precisão no resultado, como pode ser observado na comparação
 *
 * (d) Resultado idêntico ao da somaPar com 10, 100 e 1000 vezes mais elementos, porém com 10000 vezes mais, começa a perder a precisão (+4 de diferença em relação a SomaPar)
 *  possivelmente devido a falta de precisao do float em relação ao double
 * */
#include <stdio.h>
#include <stdlib.h>

#define VALOR 0.6f
#define NUM_ELEMENTOS 100000000

float somaSequencia( float *dados, unsigned int tam )
{
	float soma = 0.0;
	while ( tam-- )
	{
		soma += dados[tam];
	}

	return soma;
}

float somaPar( float *dados, unsigned int tam )
{
	if (tam == 2)
		return dados[0] + dados[1];
	if (tam == 1)
		return dados[0];

	unsigned int div = tam / 2;

	return somaPar(dados, div) + somaPar(dados+div, tam-div);
}

/* algoritmo de kahan */
float somaKahan( float *dados, unsigned int tam ){
	float soma = 0.0f;
	float c = 0.0f;

	for(unsigned int i = 0; i < tam; i++){
		float y = dados[i] - c;
		float t = soma + y;
		c = (t - soma) - y;
		soma = t;
	}

	return soma;
}

int main()
{
	// Preenche um vetor
	float *dados = (float*) malloc(NUM_ELEMENTOS * sizeof(float));

	for (unsigned int i = 0; i < NUM_ELEMENTOS; ++i)
		dados[i] = VALOR;

	float soma1 = somaSequencia( dados, NUM_ELEMENTOS );
	printf("Soma sequencia: %1.15f\n", soma1);

	float soma2 = somaPar( dados, NUM_ELEMENTOS );
	printf("Soma par:       %1.15f\n", soma2);

	float soma3 = somaKahan( dados, NUM_ELEMENTOS );
   printf("Soma Kahan:     %1.15f\n", soma3);

	free (dados);
}