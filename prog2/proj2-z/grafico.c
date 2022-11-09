#include "grafico.h"

/*cria display e estruturas do jogo*/
Game iniciaJogo(int w, int h){
   int i;
   Game jogo;

   /*inicia biblioteca e instala adicionais*/
   al_init();
   al_install_keyboard();
   al_install_mouse();
   al_install_audio();
   al_install_keyboard();
   al_init_font_addon();
   al_init_image_addon();
   al_init_ttf_addon();
   al_init_primitives_addon();
   al_init_acodec_addon();

   /*busca pela resolucao desejada ou a mais proxima*/
   for(i = 0; i < al_get_num_display_modes(); i++){
      al_get_display_mode(i, &jogo.disp_m);
      if(jogo.disp_m.width <= w && jogo.disp_m.height <= h && jogo.disp_m.refresh_rate == 60){
         break;
      }
   }
   al_get_display_mode(i, &jogo.disp_m);
   al_set_new_display_flags(ALLEGRO_WINDOWED);
   /*mudar resolucao*/
   jogo.disp_m.width = 670;
   jogo.disp_m.height = 900;
   jogo.disp = al_create_display(jogo.disp_m.width, jogo.disp_m.height);
   
   /*cria timer e fila e registra as fontes de eventos na fila*/
   jogo.timer = al_create_timer(1.0 / jogo.disp_m.refresh_rate);
   jogo.fila = al_create_event_queue();
   al_register_event_source(jogo.fila, al_get_mouse_event_source());
   al_register_event_source(jogo.fila, al_get_keyboard_event_source());
   al_register_event_source(jogo.fila, al_get_display_event_source(jogo.disp));
   al_register_event_source(jogo.fila, al_get_timer_event_source(jogo.timer));
   
   jogo.sfx = malloc(sizeof(Sound));
   al_reserve_samples(16);
   jogo.sfx->soundon = true;
   jogo.sfx->title = al_load_sample("./resources/Title.ogg");
   jogo.sfx->game = al_load_sample("./resources/Game.ogg");
   jogo.sfx->hit = al_load_sample("./resources/Hit.ogg");
   jogo.sfx->over = al_load_sample("./resources/Over.ogg");
   jogo.sfx->item = al_load_sample("./resources/Item.ogg");
	jogo.sfx->easteregg = al_load_sample("./resources/Easter.ogg");
   jogo.icon = al_load_bitmap("./resources/icon.png");
   jogo.font = al_load_font("./resources/PixelF.ttf", 36, 0);
   jogo.pontos = 0;

   al_flip_display();
   al_start_timer(jogo.timer);

   return jogo;
}

ALLEGRO_BITMAP *iniciaBitmap(char *nomeArq, int w, int h, Game *j){
   ALLEGRO_BITMAP *bmp, *img;

   bmp = al_create_bitmap(w, h);
   al_set_target_bitmap(bmp);
   al_clear_to_color(al_map_rgb(255, 255, 255));
   
   if (nomeArq) {
      img = al_load_bitmap(nomeArq);
      al_draw_bitmap(img,0,0,0);
   }
   
   al_set_target_bitmap(al_get_backbuffer(j->disp));

   return bmp;
}