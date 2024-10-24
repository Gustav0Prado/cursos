#include <stdio.h>

int ehsub(int ind, int prox, int tam, int *vet, int *endseq){       /*procura dois numeros iguais*/
	int seq = 1;													/*se achar devolve o tam da sequencia*/
	int i = 0;														/*e endereço do começo da seq*/
	if(vet[ind] == vet[prox]){
		*endseq = ind;
		int i = 1;
		while((vet[ind + i] == vet[prox + i]) && prox + i < tam){      /*procura por nums iguais na sequencia*/
			i++;													  /*até o fim do vetor*/
			seq++;	
		}
	}
	return seq;
}

void leVet(int tam, int *vet){          /*le o vetor com tamanho tam*/
	for(int i = 0; i < tam; i++){
		scanf("%d", &vet[i]);
	}
}

int analisa(int tam, int *vet, int *pos){         /*analisa os elemntos e procura e guarda sequencias*/
	int tamseqmax = 2;						 			  /*salva sempre a maior sequencia*/
	int endseq;												  /*end da sequencia atual*/
	for(int ind = 0; ind < tam; ind++){				  /*indica o elemento analisado*/
		for(int prox = ind + 1; prox < tam; prox++){ 			      /*indica o prox elemento analisado*/
			int tamseq = ehsub(ind, prox, tam, vet, &endseq);        /*manda &endseq, pois será salvo junto com*/
			if(tamseq >= tamseqmax){											   /*salva a sequencia maior e posicao*/
				tamseqmax = tamseq;
				*pos = endseq;
			}
		}
	}
	return tamseqmax;                 /*retorna o tamanho da seq, posicao foi alterado com ponteiro*/
}

int main(){
	int tam, tamanhoseq, posicao;                  /*inicializa inteiros*/
	int vet[100];		 	                			  /*vetor com 0 < n <= 100*/
	printf("insira o tamanho do vetor: ");
	scanf("%d", &tam);
	if(tam > 0 && tam <= 100){		         /*executa a função somente se estiver nos limites*/
		leVet(tam, vet);
		tamanhoseq = analisa(tam, vet, &posicao);    /*recebe o tamanho e envio o endereco de posicao para ser alterado*/
		if(tamanhoseq>= 2){
			printf("%d %d\n", posicao + 1, tamanhoseq);  /*no enunciado posicoes comecam em 1*/
		}
		else
			printf("nenhuma\n");
	}
	else
		printf("vetor fora dos limites 0 < tam <= 100\n");

	return 0;
}

