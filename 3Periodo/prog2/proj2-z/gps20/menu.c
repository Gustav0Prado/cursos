#include "pausa.h"
#include "jogoutils.h"
#include <string.h>

/*Mostra menu inicial e informacoes do jogo*/
int Inicia(Game *jogo){
	ALLEGRO_BITMAP *b1, *b2, *t, *mon, *moff, *info;
	ALLEGRO_EVENT event;
	bool done = false,
			soundini = jogo->sfx->soundon;
	int estado = JOGANDO;
	int high;
	char max[50];

	FILE *arq;

	arq = fopen("./score.dat", "a+");
	if(!arq){
		perror("Erro ao abrir arquivo de highscores");
		exit(1);
	}

	rewind(arq);
	char c = fgetc(arq);
	//arquivo vazio
	if(c == EOF){
		jogo->high = 0;
	}
	else{
		//retorna ao inico e le pontuacao
		rewind(arq);
		fread(&high, sizeof(int), 1, arq);
		jogo->high = high;
	}
	fclose(arq);

	/*arruma titulo da janela e icone do jogo*/
	al_set_window_title(jogo->disp, "Ballz");
	al_set_display_icon(jogo->disp, jogo->icon);

	/*carrega bitmaps e posiciona bitmaps e textos*/
	al_clear_to_color(al_map_rgb(0, 0, 0));
	b1 = al_load_bitmap("./resources/b1.png");
	b2 = al_load_bitmap("./resources/b2.png");
	t = al_load_bitmap("./resources/title.png");
	info = al_load_bitmap("./resources/info.png");
	sprintf(max, "%d", jogo->high);
	desenhaMenu(b1, b2, t, info, (jogo->disp_m.width/2), jogo->font, max);
	tocaMusica(jogo->sfx->soundon, jogo->sfx->title, ALLEGRO_PLAYMODE_LOOP);

	/*botoes de musica ligada e desligada, comeca ligada por padrao*/
	mon = al_load_bitmap("./resources/musicOn.png");
	moff = al_load_bitmap("./resources/musicOff.png");
	if(jogo->sfx->soundon){
		al_draw_bitmap(mon, 5, 5, 0);
	}
	else{
		al_draw_bitmap(moff, 5, 5, 0);
	}

	int b1x = (jogo->disp_m.width/2);
	int b1y = 350;

	al_flip_display();
	
	while(!done){
		al_wait_for_event(jogo->fila, &event);
		switch(event.type){
			/*registra a posicao apenas ao levantar o mouse*/
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				/*botao de jogar*/
				if((event.mouse.x >= b1x-(btnw/2) && event.mouse.x <= b1x+(btnw/2)) && (event.mouse.y >= b1y-btnh && event.mouse.y <= b1y+btnh)){
					done = true;
					estado = JOGANDO;
				}
				/*botao de sair*/
				else if((event.mouse.x >= b1x-(btnw/2) && event.mouse.x <= b1x+(btnw/2)) && (event.mouse.y >= 500-btnh && event.mouse.y <= 500+btnh)){
					done = true;
					estado = FINAL;
				}
				/*botao de som*/
				else if((event.mouse.x >= 5 && event.mouse.x <= 45) && (event.mouse.y >= 5 && event.mouse.y <= 45)){
					/*muda estado do som e para de tocar*/
					if(jogo->sfx->soundon){
						jogo->sfx->soundon = false;
						desenhaMenu(b1, b2, t, info, (jogo->disp_m.width/2), jogo->font, max);
						al_draw_bitmap(moff, 5, 5, 0);
						al_flip_display();
						paraSom();
					}
					else{
						/*comecou sem som, inicia a musica de fundo*/
						if(soundini == false){
							jogo->sfx->soundon = true;
							tocaMusica(jogo->sfx->soundon, jogo->sfx->title, ALLEGRO_PLAYMODE_LOOP);
							continuaSom();
							al_draw_bitmap(mon, 5, 5, 0);
							al_flip_display();
							soundini = true;
						}
						/*apenas volta a tocar*/
						else{
							jogo->sfx->soundon = true;
							desenhaMenu(b1, b2, t, info, (jogo->disp_m.width/2), jogo->font, max);
							continuaSom();
							al_draw_bitmap(mon, 5, 5, 0);
							al_flip_display();
						}
					}
				}
				/*botao de info*/
				else if((event.mouse.x >= 5 && event.mouse.x <= 45) && (event.mouse.y >= 50 && event.mouse.y <= 95)){
					if(Info(jogo) == FINAL){
						estado = FINAL;
						done = true;
					}
					/*redesenha menu*/
					if(jogo->sfx->soundon){
						desenhaMenu(b1, b2, t, info, (jogo->disp_m.width/2), jogo->font, max);
						al_draw_bitmap(mon, 5, 5, 0);
						al_flip_display();
					}
					else{
						desenhaMenu(b1, b2, t, info, (jogo->disp_m.width/2), jogo->font, max);
						al_draw_bitmap(moff, 5, 5, 0);
						al_flip_display();
					}
				}
				break;
			/*fechou a janela*/
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				estado = FINAL;
				break;
		}
	}

	/*destroi botoes do menu*/
	al_destroy_bitmap(b1);
	al_destroy_bitmap(b2);
	al_destroy_bitmap(t);
	al_destroy_bitmap(info);
	al_destroy_bitmap(mon);
	al_destroy_bitmap(moff);
	al_stop_samples();

	return estado;
}