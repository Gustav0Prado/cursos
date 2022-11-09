#include "pausa.h"
#include "jogoutils.h"

#define btnw 300
#define btnh 68.5

/*Tela com informacoes sobre o jogo*/
int Info(Game *jogo){
	ALLEGRO_EVENT event;
	bool done = false;
	int estado = JOGANDO;
	ALLEGRO_FONT *font = al_load_font("./resources/PixelF.ttf", 25, 0);
	ALLEGRO_BITMAP *x = al_load_bitmap("./resources/x.png");
	ALLEGRO_BITMAP *inf1 = al_load_bitmap("./resources/info1.png");
	ALLEGRO_BITMAP *inf2 = al_load_bitmap("./resources/info2.png");

	/*carrega bitmaps e posiciona bitmaps e textos*/
	al_clear_to_color(al_map_rgb(0, 0, 0));
	int xx = jogo->disp_m.width-45;
	int xy = 0;	

	/*escreve as infos na tela*/
	al_draw_bitmap(x, jogo->disp_m.width-45, 0, 0);
	al_draw_bitmap(inf1, 0, 145, 0);
	al_draw_bitmap(inf2, 308, 250, 0);
	al_draw_textf(font, al_map_rgb(255,255,255), 5, 5, 0, "Jogo criado por:");
	al_draw_textf(font, al_map_rgb(255,255,255), 20, 45, 0, "Gustavo Do Prado Silva");
	al_draw_textf(font, al_map_rgb(255,255,255), 5, 85, 0, "Disciplina CI1002 - Prog2");
	al_draw_textf(font, al_map_rgb(255,255,255), 200, 125, 0, "Como jogar:");

	al_flip_display();
	
	while(!done){
		al_wait_for_event(jogo->fila, &event);
		switch(event.type){
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				/*botao de fechar*/
				if((event.mouse.x >= xx && event.mouse.x <= xx+40) && (event.mouse.y >= xy && event.mouse.y <= xy+40)){
					done = true;
					estado = JOGANDO;
				}

			/*apertar esc sai da tela*/
			case ALLEGRO_EVENT_KEY_DOWN:
				if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
					done = true;
					estado = JOGANDO;
				}
				break;

			/*janela fechada*/
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				estado = FINAL;
				break;
		}
	}

	/*destroi botoes do menu*/
	al_destroy_bitmap(x);
	al_destroy_bitmap(inf1);
	al_destroy_bitmap(inf2);

	return estado;
}

/*menu de pausa*/
int Pausa(Game *jogo, int pontos){
	ALLEGRO_BITMAP *b1, *b2, *b3, *mon, *moff, *info;
	ALLEGRO_EVENT event;
	bool done = false;
	int estado = JOGANDO;
	char max[50];

	/*carrega bitmaps e posiciona bitmaps e textos*/
	al_clear_to_color(al_map_rgb(0, 0, 0));
	b1 = al_load_bitmap("./resources/b5.png");
	b2 = al_load_bitmap("./resources/b4.png");
	b3 = al_load_bitmap("./resources/b6.png");
	info = al_load_bitmap("./resources/info.png");

	/*escreve pontos e desenha menu*/
	sprintf(max, "%d", pontos);
	desenhaPausa(b1, b2, b3, info, (jogo->disp_m.width/2), jogo->font, max);

	/*desenha botao de musica*/
	mon = al_load_bitmap("./resources/musicOn.png");
	moff = al_load_bitmap("./resources/musicOff.png");
	if(jogo->sfx->soundon){
		al_draw_bitmap(mon, (jogo->disp_m.width/2)-50, 650, 0);
	}
	else{
		al_draw_bitmap(moff, (jogo->disp_m.width/2)-50, 650, 0);
	}

	int b1x = (jogo->disp_m.width/2);

	al_flip_display();
	
	while(!done){
		al_wait_for_event(jogo->fila, &event);
		switch(event.type){
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				/*botao de continuar*/
				if((event.mouse.x >= b1x-btnw && event.mouse.x <= b1x+btnw) && (event.mouse.y >= 200-btnh && event.mouse.y <= 200+btnh)){
					done = true;
					estado = JOGANDO;
				}
				/*botao de recomecar*/
				else if((event.mouse.x >= b1x-btnw && event.mouse.x <= b1x+btnw) && (event.mouse.y >= 350-btnh && event.mouse.y <= 350+btnh)){
					done = true;
					estado = FINALPART;
				}
				/*botao de sair*/
				else if((event.mouse.x >= b1x-btnw && event.mouse.x <= b1x+btnw) && (event.mouse.y >= 500-btnh && event.mouse.y <= 500+btnh)){
					done = true;
					estado = INICIO;
				}
				/*botao de som*/
				else if((event.mouse.x >= (jogo->disp_m.width/2)-50 && event.mouse.x <= (jogo->disp_m.width/2)-5) && (event.mouse.y >= 650 && event.mouse.y <= 695)){
					/*muda estado e pra de tocar som*/
					if(jogo->sfx->soundon){
						jogo->sfx->soundon = false;
						desenhaPausa(b1, b2, b3, info, (jogo->disp_m.width/2), jogo->font, max);
						al_draw_bitmap(moff, (jogo->disp_m.width/2)-50, 650, 0);
						al_flip_display();
						paraSom();
					}
					/*volta a tocar som*/
					else{
						jogo->sfx->soundon = true;
						desenhaPausa(b1, b2, b3, info, (jogo->disp_m.width/2), jogo->font, max);
						continuaSom();
						al_draw_bitmap(mon, (jogo->disp_m.width/2)-50, 650, 0);
						al_flip_display();
					}
				}
				/*botao de info*/
				else if(((event.mouse.x >= (jogo->disp_m.width/2) && event.mouse.x <= (jogo->disp_m.width/2)+45) && (event.mouse.y >= 650 && event.mouse.y <= 695))){
					estado = Info(jogo);
					if(estado == FINAL){
						done = true;
					}
					/*redesenha menu de pausa*/
					else if(jogo->sfx->soundon){
						desenhaPausa(b1, b2, b3, info, (jogo->disp_m.width/2), jogo->font, max);
						al_draw_bitmap(mon, (jogo->disp_m.width/2)-50, 650, 0);
						al_flip_display();
					}
					else{
						desenhaPausa(b1, b2, b3, info, (jogo->disp_m.width/2), jogo->font, max);
						al_draw_bitmap(moff, (jogo->disp_m.width/2)-50, 650, 0);
						al_flip_display();
					}
				}
				break;
			
			/*fechou a janela*/
			case ALLEGRO_EVENT_KEY_DOWN:
				if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
					done = true;
					estado = JOGANDO;
				}
				break;

			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				estado = FINAL;
				break;
		}
	}

	/*destroi botoes do menu*/
	al_destroy_bitmap(b1);
	al_destroy_bitmap(b2);
	al_destroy_bitmap(info);
	al_destroy_bitmap(mon);
	al_destroy_bitmap(moff);

	return estado;
}