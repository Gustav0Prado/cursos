
#include "fim.h"
#include "jogoutils.h"

/*Mostra opcoes para voltar ao menu, tentar de novo ou sair*/
int Fimpart(Game *jogo){
	ALLEGRO_BITMAP *b1, *b2;
	ALLEGRO_EVENT event;
	bool done = false;
	int estado = JOGANDO;
	char pont[50];
	char mpont[50];
	FILE *arq;

	/*abre arquivo de highscore*/
	arq = fopen("./score.dat", "r+");
	if(!arq){
		perror("Erro ao abrir arquivo de highscores");
		exit(1);
	}

	/*caso a pontuacao seja maior que a mxaima, salva no arquivo*/
	if(jogo->pontos > jogo->high){
		jogo->high = jogo->pontos;
		fwrite(&(jogo->high), sizeof(int), 1, arq);
	}
	fclose(arq);

	/*carrega bitmaps dos botoes e posiciona eles*/
	al_clear_to_color(al_map_rgb(0, 0, 0));
	b1 = al_load_bitmap("./resources/b3.png");
	b2 = al_load_bitmap("./resources/b4.png");
	al_draw_rotated_bitmap(b1, 150, 68.5, (jogo->disp_m.width/2), 350, 0, 0);
	al_draw_rotated_bitmap(b2, 150, 68.5, (jogo->disp_m.width/2), 500, 0, 0);

	/*escreve pontuacao atual e maxima na tela*/
	sprintf(pont, "Sua pontuacao foi: %d", jogo->pontos);
	sprintf(mpont, "Maior pontuacao: %d", jogo->high);
	al_draw_text(jogo->font, al_map_rgb(255,255,255), jogo->disp_m.width/2, 180, ALLEGRO_ALIGN_CENTER, mpont);
	al_draw_text(jogo->font, al_map_rgb(255,255,255), jogo->disp_m.width/2, 120, ALLEGRO_ALIGN_CENTER, pont);

	tocaMusica(jogo->sfx->soundon, jogo->sfx->over, ALLEGRO_PLAYMODE_ONCE);

	int b1x = (jogo->disp_m.width/2);
	int b1y = 350;

	al_flip_display();
	while(!done){
		al_wait_for_event(jogo->fila, &event);
		switch(event.type){
			/*registra a posicao apenas ao levantar o mouse*/
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				/*botao de jogar*/
				if((event.mouse.x >= b1x-btnw && event.mouse.x <= b1x+btnw) && (event.mouse.y >= b1y-btnh && event.mouse.y <= b1y+btnh)){
					done = true;
					estado = JOGANDO;
				}
				/*botao de sair*/
				else if((event.mouse.x >= b1x-btnw && event.mouse.x <= b1x+btnw) && (event.mouse.y >= 500-btnh && event.mouse.y <= 500+btnh)){
					done = true;
					estado = INICIO;
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
	al_stop_samples();

	return estado;
}

/*Termina jogo, salvando pontuacao em pont.txt e liberando memoria das estrutras e do allegro*/
int Termina(Game *jogo){
   al_destroy_display(jogo->disp);
   al_destroy_timer(jogo->timer);
   al_destroy_event_queue(jogo->fila);
	al_destroy_font(jogo->font);
	al_destroy_bitmap(jogo->icon);
	al_destroy_sample(jogo->sfx->title);
	al_destroy_sample(jogo->sfx->game);
	al_destroy_sample(jogo->sfx->over);
	al_destroy_sample(jogo->sfx->hit);
	al_destroy_sample(jogo->sfx->item);
	al_destroy_sample(jogo->sfx->easteregg);
	free(jogo->sfx);

	return -1;
}