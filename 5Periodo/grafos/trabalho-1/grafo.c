#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

#define MAX_CHARS 2048

typedef struct aresta {
    char destino[MAX_CHARS];
    unsigned int peso;
    struct aresta *prox; 
} Aresta;

typedef struct vértice {
    char nome[MAX_CHARS];
    Aresta *arestas_head;
    Aresta *arestas_tail;
} Vértice;

typedef struct grafo {
    char nome[MAX_CHARS];
    Vértice vertices[1024];
    unsigned int num_vertices;
    unsigned int num_arestas;
} Grafo;

int procura_vertice(grafo *g, char *vertice) {
    int achou = -1;
    for (unsigned int i = 0; i < g->num_vertices; i++) {
        if (strcmp(g->vertices[i].nome, vertice) == 0) achou = i;
    }

    return achou;
}

void adiciona_vertice(grafo *g, char *vertice) {
    Vértice v;
    g->num_vertices++;
    strcpy(v.nome, vertice);
    v.arestas_head = NULL;
    v.arestas_tail = NULL;

    g->vertices[g->num_vertices-1] = v;
}

void adiciona_aresta(grafo *g, char *origem, char *destino, int peso) {
    int ind_origem = procura_vertice(g, origem);
    int ind_destino = procura_vertice(g, destino);
    
    g->num_arestas++;

    Aresta *nova = malloc(sizeof(Aresta));
    strcpy(nova->destino, destino);
    nova->peso = peso;
    nova->prox = NULL;

    // Lista de arestas vazia
    if (g->vertices[ind_origem].arestas_head == NULL){
        g->vertices[ind_origem].arestas_head = nova;
        g->vertices[ind_origem].arestas_tail = nova;
    }
    else {
        g->vertices[ind_origem].arestas_tail->prox = nova;
        g->vertices[ind_origem].arestas_tail = nova;
    }

    nova = malloc(sizeof(Aresta));
    strcpy(nova->destino, origem);
    nova->peso = peso;
    nova->prox = NULL;

    // Lista de arestas vazia
    if (g->vertices[ind_destino].arestas_head == NULL){
        g->vertices[ind_destino].arestas_head = nova;
        g->vertices[ind_destino].arestas_tail = nova;
    }
    else {
        g->vertices[ind_destino].arestas_tail->prox = nova;
        g->vertices[ind_destino].arestas_tail = nova;
    }
}

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
        // Remove \n da linha
        linha[strcspn(linha, "\n")] = '\0';

        // Apenas processa se não for comentario
        if ((strncmp(linha, "//", 2) != 0) && (linha[0] != '\0')){
            // Primeira linha é o nome do grafo
            if (primeira_linha){
                primeira_linha = 0;
                strcpy(g->nome, linha);
            }
            // Outras linhas de vértices e arestas
            else{
                // Linha com arestas
                if (strstr(linha, "--") != NULL) {
                    const char delim[] = " ";
                    char *token, *prim, *seg, *peso;

                    // Primeira ponta da aresta
                    prim = strtok(linha, delim);
                    if (procura_vertice(g, prim) == -1) {
                        adiciona_vertice(g, prim);
                    }

                    token = strtok(NULL, delim); // --
                    
                    // Segunda ponta da aresta
                    seg = strtok(NULL, delim);
                    if (procura_vertice(g, seg) == -1) {
                        adiciona_vertice(g, seg);
                    }

                    // Peso da aresta
                    peso = strtok(NULL, delim);
                    if (peso != NULL) {
                        int peso_int = atoi(peso);
                        adiciona_aresta(g, prim, seg, peso_int);
                    }
                    else{
                        adiciona_aresta(g, prim, seg, 0);
                    }
                }

                // Linha com vértice sem arestas
                else adiciona_vertice(g, linha);
            }
        }

    }

    /* Printa todos os vertices e arestas lidos*/
    // for (int i = 0; i < g->num_vertices; i++) {
    //     printf("Vértice %s: ", g->vertices[i].nome);
    //     Aresta *a = g->vertices[i].arestas_head;
    //     while (a != NULL) {
    //         printf("-> %s(peso %d) ", a->destino, a->peso);
    //         a = a->prox;
    //     }
    //     printf("\n");
    // }

    return g;
}

//------------------------------------------------------------------------------
// desaloca toda a estrutura de dados alocada em g
//
// devolve 1 em caso de sucesso e 0 em caso de erro

unsigned int destroi_grafo(grafo *g){
    free(g);
    return 1;
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