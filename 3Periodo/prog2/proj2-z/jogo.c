#include "jogo.h"
#include "menu.h"
#include "pausa.h"
#include "lista.h"
#include "fila.h"
#include "jogoutils.h"
#include <string.h>
#include <time.h>
#include <math.h>

int Jogo(Game *jogo){
	typedef enum {MIRA, MOVE, DESC, ESPERA, ANIMA, PAUSA} etapasJogo;
	bool done = false,
		redraw = true,
		clicked = false,
		soundini = jogo->sfx->soundon;
	ALLEGRO_EVENT event;
	Player **bolas = NULL;
	Bloco b1;
	float posx, posy;
	int pontos = 0;
	int cont = 0;
	int qtdball = 1;
	int width = jogo->disp_m.width;
	int height = jogo->disp_m.height;
	ALLEGRO_BITMAP *pbtn = al_load_bitmap("./resources/pausa.png");
	etapasJogo etapa = MIRA;
	etapasJogo etapaAnt = MIRA;
	int rotate = 0;
	int spr = 1;
	int dspr = 1;
	int etapaRet;


	char key[16];
	memset(key, 0, sizeof(key));
	int keypos = 0;

	/*inicializa estruturas*/
	listaBloco *lbl = iniciaLista();
	noBloco *aux;
	Fila *filaBolas = criaFila();

	/*semente de numeros aleatorios baseada na hora atual*/
	srand(time(NULL));

	/*inicia jogo com apenas uma bolinha*/
	bolas = realloc(bolas, sizeof(Player));
	bolas[0] = malloc(sizeof(Player));
	iniciaBola(bolas[0], width*0.5, height*0.7, 0);
	bolas[0]->cai = false;
	enfilera(filaBolas, 0);

	/*inicia primeira linha com formacao aleatoria*/
	criaLinha(lbl, 0);

	tocaMusica(jogo->sfx->soundon, jogo->sfx->game, ALLEGRO_PLAYMODE_LOOP);

	while(!done){
		al_wait_for_event(jogo->fila, &event);

		switch(event.type){
			case ALLEGRO_EVENT_TIMER:
			
				colideParedes(bolas, qtdball, width, height);

				/*movimentacao das bolinhas*/
				for(int i = 0; i < qtdball; i++){
					if(bolas[i]->move){
						if(bolas[i]->y < height-(bolas[i]->dy+bolas[i]->r)){
							if(bolas[i]->timer == 0){
								bolas[i]->x += bolas[i]->dx;
								bolas[i]->y += bolas[i]->dy;
							}
							else{
								bolas[i]->timer--;
							}
						}
						else{
							/*bolinhas se reagrupando*/
							switch(etapa){
								case ANIMA:
									/*bateu no chao e esta na posicao certa*/
									bolas[i]->y = height-bolas[i]->r;
									if((bolas[primeiroFila(filaBolas)]->x >= bolas[i]->x-10) && bolas[primeiroFila(filaBolas)]->x <= bolas[i]->x+10){
										bolas[i]->x = bolas[primeiroFila(filaBolas)]->x;
										/*checa se todas as bolinhas ja chegaram ate a lider*/
										int xd = 0;
										for(int i = 0; i < qtdball; i++){
											if(bolas[i]->x != bolas[primeiroFila(filaBolas)]->x){
												xd++;
											}
										}
										if(xd == 0){
											etapa = MOVE;
										}
									}
									/*senao continua movendo elas*/
									else{
										if(bolas[i]->x < bolas[primeiroFila(filaBolas)]->x){
											bolas[i]->x += 10;
										}
										else{
											bolas[i]->x += -10;
										}
									}
									break;

								case MOVE:
									/*arruma x da bola para evitar sair da tela*/
									if(bolas[i]->x < 5){
										bolas[i]->x = 5;
									}
									else if(bolas[i]->x > width-5){
										bolas[i]->x = width-5;
									}
									bolas[i]->y = height-bolas[i]->r;
									/*fila de bolinhas, a que chegar primeiro eh a lider*/
									if(!filaVazia(filaBolas) && bolas[primeiroFila(filaBolas)]->x != bolas[i]->x){
										etapa = ANIMA;
									}
									else{
										enfilera(filaBolas, i);
										bolas[i]->move = false;
										bolas[i]->cai = false;
										bolas[i]->dx = 0;
										bolas[i]->dy = 0;
									}
									/*todas as bolas na fila*/
									if(tamanhoFila(filaBolas) == qtdball){
										cont = 0;
										etapa = DESC;
									}
									break;

								default:
									break;
							}
						}
					}
				}

				/*checa todos os blocos se houve colisao, desce contador, aumenta pontos*/
				aux = lbl->head;
				while(aux != NULL){
					/*bloco*/
					if(aux->tipo == BLOCO){						
						b1 = *(aux->bloco);
						for(int i = 0; i < qtdball && aux != NULL; i++){
							if(!(bolas[i]->cai)  && bolas[i]->move && colisao(bolas[i], b1)){
								tocaMusica(jogo->sfx->soundon, jogo->sfx->hit, ALLEGRO_PLAYMODE_ONCE);
								reflete(bolas[i], b1);

								/*diminui contador quando atingido e deleta se chegar a zero*/
								aux->bloco->cont--;
								if(aux->bloco->cont == 0){
									pontos++;

									/*procura proximo bloco*/
									noBloco *aux2;
									if(aux->prox != NULL){
										aux2 = aux->prox;
									}
									else{
										aux2 = NULL;
									}
									removeLista(aux, lbl);
									aux = aux2;
								}
							}
						}
						/*desce blocos na tela*/
						if(etapa == DESC && cont < 32 && b1.y+b1.d < height){
							aux->bloco->y+= 3;
						}
						/*acaba jogo se chegar no fim da tela*/
						else if(b1.y+b1.d >= height){
							done = true;
							etapaRet = FINALPART;
						}
					}
					else{
						Item it = *(aux->item);
						for(int i = 0; i < qtdball && aux != NULL; i++){
							if(!(bolas[i]->cai)  && bolas[i]->move && colisaoIt(bolas[i], it)){
								tocaMusica(jogo->sfx->soundon, jogo->sfx->item, ALLEGRO_PLAYMODE_ONCE);
								/*aumenta num de bolas*/
								qtdball++;
								bolas = realloc(bolas, sizeof(Player)*qtdball);
								bolas[qtdball-1] = malloc(sizeof(Player));
								iniciaBola(bolas[qtdball-1], it.x, it.y, 0);
								bolas[qtdball-1]->dx = 0;
								bolas[qtdball-1]->dy = 15;
								bolas[qtdball-1]->move = true;
								bolas[qtdball-1]->cai = true;

								/*procura proximo bloco*/
								noBloco *aux2;
								if(aux->prox != NULL){
									aux2 = aux->prox;
								}
								else{
									aux2 = NULL;
								}
								removeLista(aux, lbl);
								aux = aux2;
								break;
							}
						}
						/*desce blocos na tela*/
						if(etapa == DESC && cont < 32 && it.y+it.d < height){
							aux->item->y+= 3;
						}
						else if(it.y+it.d >= height){
							removeLista(aux, lbl);
						}
					}
					if(aux != NULL){
						aux = aux->prox;
					}
				}
				cont++;
				/*cria linha nova depois de descer anterior*/
				if(etapa == DESC && cont == 32){
					criaLinha(lbl, pontos);
					etapa = MIRA;
				}

				redraw = true;
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				if(etapa != MOVE){
					clicked  = true;
				}
				/*muda para tela de pausa, salvando estado atual*/
				if((event.mouse.x >= 0 && event.mouse.x <= 40) && (event.mouse.y >= 0 && event.mouse.y <= 40)){					
					etapaAnt = etapa;
					etapa = PAUSA;
					/*salva movimento de cada bolinhas*/
					bool moveant[qtdball];
					for(int i = 0; i < qtdball; i++){
						moveant[i] = bolas[i]->move;
						bolas[i]->move = false;
					}
					/*muda para telade pausa
					muda de estado caso saiu do jogo ou mudou para o menu*/
					bool soundest = jogo->sfx->soundon;
					int est = Pausa(jogo, pontos);
					/*se som comecou pausado e foi trocado o estado, comeca a tocar a musica*/
					if(soundest != jogo->sfx->soundon && jogo->sfx->soundon && !soundini){
						tocaMusica(jogo->sfx->soundon, jogo->sfx->game, ALLEGRO_PLAYMODE_LOOP);
						soundini = true;
					}
					switch(est){
						case JOGANDO:
							/*continua o jogo, restaura o movimento das bolinhas*/
							etapa = etapaAnt;
							for(int i = 0; i < qtdball; i++){
								bolas[i]->move = moveant[i];
							}
							break;
						case INICIO:
							done = true;
							etapaRet = INICIO;
							break;
						case FINALPART:
							done = true;
							etapaRet = JOGANDO;
							break;
						case FINAL:
							done = true;
							etapaRet = FINAL;
							break;
					}
				}
				break;

			/*captura posicao do mouse para calcular direcao da bola*/
			case ALLEGRO_EVENT_MOUSE_AXES:
				posx = event.mouse.x;
				posy = event.mouse.y;
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				if(etapa == MIRA){
					for(int i = 0; i < qtdball; i++){
						/*tira bolas da fila e seta velocidade e timer*/
						if(!filaVazia(filaBolas)){
							int atual = desenfilera(filaBolas);
							if(!(bolas[atual]->move)){
							/*funcoes para as expressoes*/
								float dir = atan2((posy - bolas[0]->y), (posx - bolas[0]->x));
								bolas[atual]->dx = 15*cos(dir);
								bolas[atual]->dy = 15*sin(dir);
								bolas[atual]->timer = i*6;
								bolas[atual]->move = true;
							}
						}
					}
					etapa = MOVE;
					clicked = false;
				}
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				/*esq pausa o jogo*/				
				if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
					etapaAnt = etapa;
					etapa = PAUSA;
					bool moveant[qtdball];
					for(int i = 0; i < qtdball; i++){
						moveant[i] = bolas[i]->move;
						bolas[i]->move = false;
					}
					int est = Pausa(jogo, pontos);
					switch(est){
						case JOGANDO:
							/*continua o jogo, restaura o movimento das bolinhas*/
							etapa = etapaAnt;
							for(int i = 0; i < qtdball; i++){
								bolas[i]->move = moveant[i];
							}
							break;
						case INICIO:
							done = true;
							etapaRet = INICIO;
							break;
						case FINALPART:
							done = true;
							etapaRet = JOGANDO;
							break;
						case FINAL:
							done = true;
							etapaRet = FINAL;
							break;
					}
				}
				/*h ou f1 mostam infos*/
				else if(event.keyboard.keycode == ALLEGRO_KEY_F1 || event.keyboard.keycode == ALLEGRO_KEY_H){
					Info(jogo);
				}
				else{
					if(event.keyboard.keycode == ALLEGRO_KEY_F5){
						keypos = 0;
					}
					else if(keypos < 14){
						key[keypos] = event.keyboard.keycode+64;
						keypos++;
					}
					else if(keypos == 14){
						key[keypos] = event.keyboard.keycode+64;
						/*se o coidgo for o certo, duplica o numero de bolas na tela*/
						/*no maximo 100 por vez*/
						if(strcmp(key, "CLONEDASSOMBRAS") == 0 && qtdball <= 50){
							int qtdorig = qtdball;
							qtdball = qtdball*2;
							for(int i = qtdorig; i < qtdball; i++){
								tocaMusica(jogo->sfx->soundon, jogo->sfx->easteregg, ALLEGRO_PLAYMODE_ONCE);
								/*aumenta bolas*/
								bolas = realloc(bolas, sizeof(Player)*qtdball);
								bolas[i] = malloc(sizeof(Player));
								iniciaBola(bolas[i], (100*(i-qtdorig))+10, 15, 0);
								bolas[i]->dx = 0;
								bolas[i]->dy = 15;
								bolas[i]->move = true;
								bolas[i]->cai = true;
								etapa = ANIMA;
							}
						}
						keypos = 0;
					}

				}
				break;

			/*Termina jogo caso feche a janela*/
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				done = true;
				etapaRet = FINAL;
				break;
		}

		/*desenha na tela os bitmaps e texto da pontuacao*/
		if(redraw && al_event_queue_is_empty(jogo->fila)){
			char pontua[15];
			al_clear_to_color(al_map_rgb(0, 0, 0));

			/*escreve pontuacao atual na tela*/
			sprintf(pontua, "%d", pontos);
			al_draw_text(jogo->font, al_map_rgb(255, 255, 255), jogo->disp_m.width-40, 10, 0, pontua);

			/*mover todas as bolas*/
			for(int i = 0; i < qtdball; i++){
				/*animacao de cair ao pegar uma bolinha, pinta ela de verde para diferenciar*/
				if(!(bolas[i]->cai)){
					al_draw_rotated_bitmap(bolas[i]->bmp, 5, 5, bolas[i]->x, bolas[i]->y, 0, 0);
				}
				else{
					al_draw_tinted_rotated_bitmap(bolas[i]->bmp, al_map_rgb(0,181,0), 5, 5, bolas[i]->x, bolas[i]->y, 0, 0);
				}
			}
			
			al_draw_rotated_bitmap(pbtn, 5, 5, 5, 5, 0, 0);

			/*desenha todos os blocos da lista e os contadores dentro deles*/
			aux = lbl->head;
			while(aux != NULL){
				if(aux->tipo == BLOCO){
					b1 = *(aux->bloco);
					desenhaBloco(b1, jogo->font);
				}
				/*desenha item com rotacao e animacao*/
				else{
					if(spr <= 7){
						if(spr == 0){
							dspr = 1;
						}
						al_draw_rotated_bitmap(aux->item->anim1, (aux->item->d/2), (aux->item->d/2), aux->item->x, aux->item->y, rotate*(3.14)/180, 0);
					}
					else{
						if(spr == 14){
							dspr = -1;
						}
						al_draw_rotated_bitmap(aux->item->anim2, (aux->item->d/2), (aux->item->d/2), aux->item->x, aux->item->y, rotate*(3.14)/180, 0);
					}
					al_draw_filled_circle(aux->item->x, aux->item->y, 20, al_map_rgb(255,255,255));
					if(rotate == 360){
						rotate = 0;
					}	
					else{
						rotate+=1;
					}

					spr += dspr;
				}
				aux = aux->prox;
			}
			/*mira com bolinhas*/
			if(clicked && etapa == MIRA){
				mira(*(bolas[0]), posx, posy, qtdball);
			}

			al_flip_display();
			redraw = false;
		}
	}

	/*salva pontuacao, para musicas e libera memoria das bolinhas, fila e lista*/
	jogo->pontos = pontos;
	al_stop_samples();
	for(int i = 0; i < qtdball; i++){
		al_destroy_bitmap(bolas[i]->bmp);
		free(bolas[i]);
	}
	free(bolas);
	destroiFila(filaBolas);
	destroiLista(lbl);

	return etapaRet;
}