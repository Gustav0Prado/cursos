#include "grafico.h"

#define W 1024
#define H 768

#define btnw 300
#define btnh 68.5

#ifndef GMS1_H__
#define GMS1_H__

typedef enum {INICIO, JOGANDO, FINALPART, FINAL} Estado;

int Inicia(Game *jogo);

int Jogo(Game *jogo);

int Fimpart(Game *jogo);

int Termina(Game *jogo);

#endif