#include "jogoutils.h"
#include <math.h>

void iniciaBola(Player *bola, int x, int y, int timer){
	bola->bmp = al_load_bitmap("./resources/ball.png");
	bola->x = x;
	bola->y = y;
	bola->r = 5;
	bola->timer = timer;
	bola->move = false;
}

/*inica um bloco em uma posicao*/
Bloco *iniciaBloco(int x, int y, int c){
	Bloco *b = malloc(sizeof(Bloco));
	b->bmp = al_load_bitmap("./resources/quad.png");
	b->d = 90;
	b->x = x;
	b->y = y;
	b->cont = c;

	return b;
}

/*inica um bloco em uma posicao*/
Item *iniciaItem(int x, int y){
	Item *i = malloc(sizeof(Item));
	i->anim1 = al_load_bitmap("./resources/itemt2.png");
	i->anim2 = al_load_bitmap("./resources/itemt3.png");
	i->d = 90;
	i->x = x;
	i->y = y;

	return i;
}

/*retorna se elemento ainda nao existe no vetor*/
int naorepete(int a, int vet[], int tam){
	if(tam > 0){
		for(int i = 0; i < tam; i++){
			if(a == vet[i]){
				return 0;
			}
		}
		return 1;
	}
	return 1;
}

/*cria linha de blocos sem repetir posicoes*/
void criaLinha(listaBloco *lbl, int pontos){
	int esp = 95;
	/*1-7 blocos podem ser criados*/
	int r =  (pontos < 30 ? (rand() %7) : 5);
	int i = 0;
	r++;
	int pos[r];
	/*cria blocos e insere apenas se nao repetir as posicoes*/
	while(i < r){
		/*posicoes 0-6*/
		int r2 = (rand() %7);
		if(naorepete(r2, pos, i)){
			pos[i] = r2;
			/*1/3 de chance do prox bloco ter o dobro de "vida"*/
			int chance = ((rand() % 3)+1) == 3;
			int moeda = ((rand() % 2)) == 1;
			if(r > 1  && (i == r-1) && moeda){
				insereLista(NULL, (iniciaItem(50+(r2*esp), 185)), lbl);
			}
			else{
				if(pontos == 0){
					if(chance){
						insereLista(iniciaBloco(5+(r2*esp), 140, 2), NULL, lbl);
					}
					else{
						insereLista(iniciaBloco(5+(r2*esp), 140, 1), NULL, lbl);
					}
				}
				else{
					if(chance){
						insereLista(iniciaBloco(5+(r2*esp), 140, pontos*2), NULL, lbl);
					}
					else{
						insereLista(iniciaBloco(5+(r2*esp), 140, pontos), NULL, lbl);
					}
				}
			}
			i++;
		}
	}
}

/*toca sample se on for true*/
void tocaMusica(bool on, ALLEGRO_SAMPLE *sample, ALLEGRO_PLAYMODE mode){
	if(on){
		al_play_sample(sample, 0.5, 0.0, 1.0, mode, NULL);
	}
}

/*para mixer de musica*/
void paraSom(){
	al_set_mixer_playing(al_get_default_mixer(), false);
}

/*inicia mixer de musica*/
void continuaSom(){
	al_set_mixer_playing(al_get_default_mixer(), true);
}

/*redesenha menu principal*/
void desenhaMenu(ALLEGRO_BITMAP *b1, ALLEGRO_BITMAP *b2, ALLEGRO_BITMAP *t, ALLEGRO_BITMAP *info, float width, ALLEGRO_FONT *font, char *max){
   al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_rotated_bitmap(b1, 150, 68.5, width, 350, 0, 0);
	al_draw_rotated_bitmap(b2, 150, 68.5, width, 500, 0, 0);
	al_draw_rotated_bitmap(t, 150, 70, width, 200, 0, 0);
	al_draw_bitmap(info, 5, 50, 0);
   al_draw_text(font, al_map_rgb(255,255,255), (width*2)-50, 5, 0, max);
}

void desenhaPausa(ALLEGRO_BITMAP *b1, ALLEGRO_BITMAP *b2, ALLEGRO_BITMAP *b3, ALLEGRO_BITMAP *info, float width, ALLEGRO_FONT *font, char *max){
   al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_rotated_bitmap(b1, 150, 68.5, width, 200, 0, 0);
	al_draw_rotated_bitmap(b3, 150, 68.5, width, 350, 0, 0);
	al_draw_rotated_bitmap(b2, 150, 68.5, width, 500, 0, 0);
	al_draw_bitmap(info, width, 650, 0);
   al_draw_text(font, al_map_rgb(255,255,255), (width*2)-30, 5, 0, max);
}

/*norma de um vetor*/
float norma(float x, float y){
	return (sqrt(x * x + y * y));
}

/*retorna se houve ou nao colisao entre a bola e um bloco*/
int colisao(Player *bola, Bloco b1){
	float cx = bola->x+bola->dx;
	float cy = bola->y+bola->dy;
	float testX = cx;
	float testY = cy;

	//esq
	if (cx < b1.x){
		testX = b1.x;
	}
	//dir
	else if (cx > b1.x+b1.d){
		testX = b1.x+b1.d;
	}
	//cima
	if (cy < b1.y){
		testY = b1.y;
	}
	//baixo
	else if (cy > b1.y+b1.d){
		testY = b1.y+b1.d;
	}

	// get distance from closest edges
	float distX = cx-testX;
	float distY = cy-testY;
	float distance = sqrt( (distX*distX) + (distY*distY) );

	// if the distance is less than the radius, collision!
	if (distance <= bola->r) {
		return 1;
	}
	return 0;
}

/*retorna se houve ou nao colisao entre a bola e um bloco*/
int colisaoIt(Player *bola, Item b1){
	float cx = bola->x+bola->dx;
	float cy = bola->y+bola->dy;
	float testX = cx;
	float testY = cy;

	//esq
	if (cx < b1.x-(b1.d/2)){
		testX = b1.x;
	}
	//dir
	else if (cx > b1.x+(b1.d/2)){
		testX = b1.x+b1.d;
	}
	//cima
	if (cy < b1.y-(b1.d/2)){
		testY = b1.y;
	}
	//baixo
	else if (cy > b1.y+(b1.d/2)){
		testY = b1.y+b1.d;
	}

	// get distance from closest edges
	float distX = cx-testX;
	float distY = cy-testY;
	float distance = sqrt( (distX*distX) + (distY*distY) );

	// if the distance is less than the radius, collision!
	if (distance <= bola->r) {
		return 1;
	}
	return 0;
}

void colideParedes(Player **bolas, int qtdball, int width, int height){
	for(int i = 0; i < qtdball; i++){
		if((bolas[i]->x > width-bolas[i]->r && bolas[i]->y < bolas[i]->r) || (bolas[i]->x < bolas[i]->r && bolas[i]->y < bolas[i]->r)){
			bolas[i]->dx = -bolas[i]->dx;
			bolas[i]->dy = -bolas[i]->dy;
		}
		else if(bolas[i]->x <= bolas[i]->r || bolas[i]->x+bolas[i]->r >= width){
			bolas[i]->dx = -bolas[i]->dx;
		}
		else if(bolas[i]->y <= bolas[i]->r){
			bolas[i]->dy = -bolas[i]->dy;
		}
	}
}


void mira(Player bola, int posx, int posy, int qtdball){
	ALLEGRO_BITMAP *tri = al_load_bitmap("./resources/triang.png");
	ALLEGRO_FONT *minifont =  al_load_font("./resources/PixelF.ttf", 15, 0);
	char qtdbolas[50];

	/*rotaciona o triangulo de acordo com a rotacao da bolinha*/
	float dist = sqrtf( ((bola.x-posx)*(bola.x-posx)) + ((bola.y-posy)*(bola.y-posy)) );
	int q = floorf(dist/20);
	/*distancia curta, desesnha bolinhas menores*/
	if(q < 10 && q > 0){
		for(float i = 0; i < q; i++){
			al_draw_filled_circle(bola.x-((bola.x-posx)*(i/(q-1))), bola.y-((bola.y-posy)*(i/(q-1))), 2, al_map_rgb(255,255,255));
			al_draw_rotated_bitmap(tri, 10, 30, (bola.x-((bola.x-posx)*0.05)), (bola.y-((bola.y-posy)*0.05)), atan2(posx-bola.x, -(posy-bola.y)), 0);
		}
	}
	/*distancia maior, desenha bolinhas maiores*/
	else if(q > 0){
		for(float i = 3; i < q; i++){
			al_draw_filled_circle(bola.x-((bola.x-posx)*(i/(q-1))), bola.y-((bola.y-posy)*(i/(q-1))), 4, al_map_rgb(255,255,255));
			al_draw_rotated_bitmap(tri, 10, 30, (bola.x-((bola.x-posx)*0.05)), (bola.y-((bola.y-posy)*0.05)), atan2(posx-bola.x, -(posy-bola.y)), 0);
		}
	}
	sprintf(qtdbolas, "x%d", qtdball);
	al_draw_text(minifont, al_map_rgb(255,255,255), bola.x+10, bola.y-10, 0, qtdbolas);
	
	al_destroy_font(minifont);
	al_destroy_bitmap(tri);
}

void desenhaBloco(Bloco b1, ALLEGRO_FONT *font){
	char bcont[4];
	sprintf(bcont, "%d", b1.cont);
	/*colocar em funcao*/
	/*amarelo*/
	if(b1.cont < 8)
		al_draw_tinted_bitmap(b1.bmp, al_map_rgb(255, 195, 0), b1.x, b1.y, 0);
	/*verde*/
	else if(b1.cont < 14){
		al_draw_tinted_bitmap(b1.bmp, al_map_rgb(0, 255, 0), b1.x, b1.y, 0);
	}
	/*vermelho*/
	else if(b1.cont < 40){
		al_draw_tinted_bitmap(b1.bmp, al_map_rgb(255, 0, 0), b1.x, b1.y, 0);
	}
	/*azul*/
	else{
		al_draw_tinted_bitmap(b1.bmp, al_map_rgb(0, 0, 255), b1.x, b1.y, 0);
	}
	al_draw_text(font, al_map_rgb(255, 255, 255), b1.x+45, b1.y+30, ALLEGRO_ALIGN_CENTER, bcont);
}

void reflete(Player *bola, Bloco b1){
	/*bola passa raspando por cima*/
	if((bola->x <= b1.x && bola->y <= b1.y) || (bola->x >= b1.x+b1.d && bola->y <= b1.y)){
		bola->dx = -bola->dx;
	}
	/*bola na esquerda ou na direita*/
	else if((bola->x <= b1.x && bola->y >= b1.y) || (bola->x >= b1.x+b1.d && bola->y >= b1.y)){
		bola->dx = -bola->dx;
	}
	else if((bola->x >= b1.x && bola->y >= b1.y+b1.d) || (bola->x >= b1.x && bola->y <= b1.y)){
		bola->dy = -bola->dy;
	}
	/*bola passa raspando em algum lado*/
	else{
		bola->dy = -bola->dy;
	}
}