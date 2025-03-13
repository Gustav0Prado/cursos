#include <stdlib.h>
#include "game.h"
#include "set.h"
#include "sat.h"

/**
 * Le saida do SAT Solver e coloca em uma matriz
 */
void read_outuput(Game *g){
    FILE *result = fopen("result.sat", "r");

    char buff[256];

    fgets (buff, sizeof(buff), result);
    for (int i = 0; i < (*g).lines; i++) {
        for (int j = 0; j < (*g).cols; j++) {
            fscanf(result, "%s", buff);
            if (atoi(buff) < 0) {
                (*g).res[i][j] = 0;
            }
            else{
                (*g).res[i][j] = 1;
            }
        }
    }

    fclose(result);
}

/**
 * Insere infos do sat (DIMACS) no inicio do arquivo
 */
void prepend(Game g){
    FILE *orig = fopen("formula.sat", "r+");
    FILE *temp = fopen("temp.sat", "w+");

    char c;    // this must be an int
    int count = 0;
    for (c = getc(orig); c != EOF; c = getc(orig)) {
        if (c == '\n') {
            count = count + 1;
        }
    }

    // printa header do DIMACS
    fprintf(temp, "p cnf %d %d\n", g.cols*g.lines, count);

    // Copia contéudo da origem pro temp
    rewind(orig);
    while ( (c = fgetc(orig)) != EOF ){
        fputc(c, temp);
    }

    // Copia contéudo do temp pra origem de novo
    rewind(temp);
    rewind(orig);
    while ((c = fgetc(temp)) != EOF){
        fputc(c, orig);
    }

    fclose(orig);
    fclose(temp);
    system("rm -f temp.sat");
}

/**
 * Retorna os indices únicos dos vizinhos de uma célula
 */
void pick_neighbors(Game g, int (*arr)[], int i, int j){
    (*arr)[0] = ind(g, i-1, j-1);
    (*arr)[1] = ind(g, i-1, j);
    (*arr)[2] = ind(g, i-1, j+1);
    (*arr)[3] = ind(g, i, j-1);
    (*arr)[4] = ind(g, i, j+1);
    (*arr)[5] = ind(g, i+1, j-1);
    (*arr)[6] = ind(g, i+1, j);
    (*arr)[7] = ind(g, i+1, j+1);
}


/**
 * Loop principal que processa o jogo
 */
void start_game(Game *g){
    FILE* f = fopen("formula.sat", "wr");

    for (int i = 1; i < (*g).lines-1; i++){
        for (int j = 1; j < (*g).cols-1; j++){
            if ((*g).matrix[i][j] == 0){
                // Calcula preservation
                Set s;
                s.elem = ind((*g), i, j);
                s.subset_size = PRESERVATION_S_SIZE;
                s.size = 8;

                int set[s.size];
                int temp[s.subset_size];

                s.arr = set;
                s.subset = temp;

                pick_neighbors((*g), &set, i, j);
                generate_subsets((*g), s, 0, 0, f, preservation);

                // Calcula life
                s.subset_size = LIFE_S_SIZE;

                int set_2[s.size];
                int temp_2[s.subset_size];

                s.arr = set_2;
                s.subset = temp_2;

                pick_neighbors((*g), &set_2, i, j);
                generate_subsets((*g), s, 0, 0, f, life);
            }
            else {
                // Calcula loneliness
                Set s;
                s.elem = ind((*g), i, j);
                s.subset_size = LONELINESS_S_SIZE;
                s.size = 8;

                int set[s.size];
                int temp[s.subset_size];

                s.arr = set;
                s.subset = temp;

                pick_neighbors((*g), &set, i, j);
                generate_subsets((*g), s, 0, 0, f, loneliness);

                // Calcula stagnation
                s.subset_size = STAGNATION_S_SIZE;

                int set_2[s.size];
                int temp_2[s.subset_size];

                s.arr = set_2;
                s.subset = temp_2;

                pick_neighbors((*g), &set_2, i, j);
                generate_subsets((*g), s, 0, 0, f, stagnation);

                // Calcula overcrowding
                s.subset_size = OVERCROWDING_S_SIZE;

                int set_3[s.size];
                int temp_3[s.subset_size];

                s.arr = set_2;
                s.subset = temp_2;

                pick_neighbors((*g), &set_3, i, j);
                generate_subsets((*g), s, 0, 0, f, overcrowding);
            }
        }
    }


    fclose(f);
    prepend((*g));

    system("./utils/minisat formula.sat result.sat");

    read_outuput(g);
}