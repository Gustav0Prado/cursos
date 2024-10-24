#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#ifndef GMS_H__
#define GMS_H__

typedef enum {BLOCO, ITEM} EItem;

typedef struct s_sound{
   bool soundon;
   ALLEGRO_SAMPLE *title;
   ALLEGRO_SAMPLE *game;
   ALLEGRO_SAMPLE *hit;
   ALLEGRO_SAMPLE *over;
   ALLEGRO_SAMPLE *item;
   ALLEGRO_SAMPLE *easteregg;
} Sound;

typedef struct s_game{
   ALLEGRO_TIMER *timer;
   ALLEGRO_DISPLAY *disp;
   ALLEGRO_DISPLAY_MODE disp_m;
   ALLEGRO_EVENT_QUEUE *fila;
   ALLEGRO_BITMAP *icon;
   ALLEGRO_FONT *font;
   Sound *sfx;
   int pontos;
   int high;
} Game;

typedef struct s_player{
   ALLEGRO_BITMAP *bmp;
   float x;
   float y;
   float dx;
   float dy;
   int r;
   int timer;
   bool move;
   bool cai;
} Player;

typedef struct s_bloco{
   ALLEGRO_BITMAP *bmp;
   float x;
   float y;
   float d;
   int cont;
} Bloco;

typedef struct s_item{
   ALLEGRO_BITMAP *anim1;
   ALLEGRO_BITMAP *anim2;
   float x;
   float y;
   float d;
} Item;

/*cria display e estruturas do jogo*/
Game iniciaJogo(int w, int h);

ALLEGRO_BITMAP *iniciaBitmap(char *nomeArq, int w, int h, Game *j);

#endif