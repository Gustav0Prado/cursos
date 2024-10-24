#include "jogo.h"
#include "lista.h"

void iniciaBola(Player *bola, int x, int y, int timer);

int naorepete(int a, int vet[], int tam);

void criaLinha(listaBloco *lbl, int pontos);

void paraSom();

void continuaSom();

void tocaMusica(bool on, ALLEGRO_SAMPLE *sample, ALLEGRO_PLAYMODE mode);

void desenhaMenu(ALLEGRO_BITMAP *b1, ALLEGRO_BITMAP *b2, ALLEGRO_BITMAP *t, ALLEGRO_BITMAP *info, float width, ALLEGRO_FONT *font, char *max);

void desenhaPausa(ALLEGRO_BITMAP *b1, ALLEGRO_BITMAP *b2, ALLEGRO_BITMAP *b3, ALLEGRO_BITMAP *info, float width, ALLEGRO_FONT *font, char *max);

Bloco *iniciaBloco(int x, int y, int c);

float norma(float x, float y);

int colisao(Player *bola, Bloco b1);

int colisaoIt(Player *bola, Item b1);

void colideParedes(Player **bolas, int qtdball, int width, int height);

void mira(Player bola, int posx, int posy, int qtdball);

void desenhaBloco(Bloco b1, ALLEGRO_FONT *font);

void reflete(Player *Bola, Bloco b1);