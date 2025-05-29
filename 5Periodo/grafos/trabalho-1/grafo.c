#include <stdio.h>
#include <string.h>
#include "grafo.h"

#define MAX_CHARS 2048

typedef struct vértice{
    char nome[MAX_CHARS];
    struct vértice *proximo;
} Vértice;


typedef struct grafo{
    char nome[MAX_CHARS];
    Vértice *vértices;
    int num_vertices;
    int num_arestas;
} Grafo;

grafo *le_grafo(FILE *f) {
    Grafo *g = malloc(sizeof(Grafo));
    if (g == NULL) {
        perror("Erro ao alocar memória para o grafo");
        return NULL;
    }

    char linha[MAX_CHARS];

    // Lê da entrada f
    int primeira_linha = 1;

    while (fgets(linha, sizeof(linha), f)) { 
        // Para quando acha uma linha vazia
        if (strcmp(linha, "\n") == 0 || linha[0] == '\0') {
            break;
        }

        // Apenas processa se não for comentario
        if (strncmp(linha, "//", 2) != 0) {
            // Primeira linha é o nome do grafo
            if (primeira_linha){
                primeira_linha = 0;
                linha[strcspn(linha, "\n")] = '\0';
                strcpy(g->nome, linha);
            }
            // Outras linhas vértices e arestas
            else{
                printf("%s\n", linha);
            }
        }

    }

    return g;
}

//------------------------------------------------------------------------------
// desaloca toda a estrutura de dados alocada em g
//
// devolve 1 em caso de sucesso e 0 em caso de erro

unsigned int destroi_grafo(grafo *g){
    return;
}

//------------------------------------------------------------------------------
// devolve o nome de g

char *nome(grafo *g){
    return (*g).nome;
}

//------------------------------------------------------------------------------
// devolve 1 se g é bipartido e 0 caso contrário

unsigned int bipartido(grafo *g){
    return;
}

//------------------------------------------------------------------------------
// devolve o número de vértices em g

unsigned int n_vertices(grafo *g){
    return g->num_vertices;
}

//------------------------------------------------------------------------------
// devolve o número de arestas em g

unsigned int n_arestas(grafo *g){
    return g->num_arestas;
}

//------------------------------------------------------------------------------
// devolve o número de componentes em g

unsigned int n_componentes(grafo *g){
    return;
}

//------------------------------------------------------------------------------
// devolve uma "string" com os diâmetros dos componentes de g separados por brancos
// em ordem não decrescente

char *diametros(grafo *g){
    return;
}

//------------------------------------------------------------------------------
// devolve uma "string" com os nomes dos vértices de corte de g em
// ordem alfabética, separados por brancos

char *vertices_corte(grafo *g){
    return;
}

//------------------------------------------------------------------------------
// devolve uma "string" com as arestas de corte de g em ordem alfabética, separadas por brancos
// cada aresta é o par de nomes de seus vértices em ordem alfabética, separadas por brancos
//
// por exemplo, se as arestas de corte são {z, a}, {x, b} e {y, c}, a resposta será a string
// "a z b x c y"

char *arestas_corte(grafo *g){
    return;
}