/* WSCAD - 9th Marathon of Parallel Programming
* Simple Brute Force Algorithm for the
* Traveling-Salesman Problem
* Author: Emilio Francesquini - francesquini@ic.unicamp.br
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <mpi.h>

int min_distance, nb_towns, rank, n_procs;

#define GET_WORK  0
#define WORK      1
#define GET_INST  2
#define MIN_DIST  3
#define END_WORK  4
#define START     5
#define NEW_WORK  6

typedef struct
{
   int to_town;
   int dist;
} d_info;

d_info **d_matrix;
int *dist_to_origin;
MPI_Status status;

void tsp(int depth, int current_length, char *path, int last)
{
   if (current_length >= min_distance)
      return;
   if (depth == nb_towns)
   {
      current_length += dist_to_origin[last];
      if (current_length < min_distance) {
         min_distance = current_length;
         MPI_Send (&min_distance, 1, MPI_INT, 0, MIN_DIST, MPI_COMM_WORLD);
      }
   }
   else
   {
      int town, me, dist;
      me = last;
      for (int i = 1; i < nb_towns; i++)
      {
         town = d_matrix[me][i].to_town;
         if (path[town] == 0)
         {
               path[town] = 1;
               dist = d_matrix[me][i].dist;
               tsp(depth + 1, current_length + dist, path, town);
               path[town] = 0;
         }
      }
   }
}

void greedy_shortest_first_heuristic(int *x, int *y)
{
   int i, j, k, dist;
   int *tempdist;

   tempdist = (int *)malloc(sizeof(int) * nb_towns);
   // Could be faster, albeit not as didactic.
   // Anyway, for tractable sizes of the problem it
   // runs almost instantaneously.
   for (i = 0; i < nb_towns; i++)
   {
      for (j = 0; j < nb_towns; j++)
      {
         int dx = x[i] - x[j];
         int dy = y[i] - y[j];
         tempdist[j] = dx * dx + dy * dy;
      }

      for (j = 0; j < nb_towns; j++)
      {
         int tmp = INT_MAX;
         int town = 0;
         for (k = 0; k < nb_towns; k++)
         {
               if (tempdist[k] < tmp)
               {
                  tmp = tempdist[k];
                  town = k;
               }
         }
         tempdist[town] = INT_MAX;
         d_matrix[i][j].to_town = town;
         dist = (int)sqrt(tmp);
         d_matrix[i][j].dist = dist;
         if (i == 0)
               dist_to_origin[town] = dist;
      }
   }

   free(tempdist);
}

void init_tsp(int *x, int *y)
{
   int i, st;

   min_distance = INT_MAX;

   d_matrix = (d_info **)malloc(sizeof(d_info *) * nb_towns);
   for (i = 0; i < nb_towns; i++)
      d_matrix[i] = (d_info *)malloc(sizeof(d_info) * nb_towns);
   dist_to_origin = (int *)malloc(sizeof(int) * nb_towns);

   greedy_shortest_first_heuristic(x, y);
}

void read_stdin(int **x, int **y){
   int st;
   
   // Le n de cidades
   st = scanf("%u", &nb_towns);
   if (st != 1){
      MPI_Abort (MPI_COMM_WORLD, 123);
   }

   *x = malloc(sizeof(int) * nb_towns);
   *y = malloc(sizeof(int) * nb_towns);

   // Le x e y
   for(int i = 0; i < nb_towns; ++i){
      st = scanf("%u %u", (*x) + i, (*y) + i);
      if (st != 2) {
         MPI_Abort (MPI_COMM_WORLD, 123);
      }
   }
}

void manager () {
   int num_instances, st, i_buff = 0, dist, pos, buff_siz, orig_inst, alive;
   char waiting[n_procs-1];

   // Le n de instancias
   st = scanf("%u", &num_instances);
   if (st != 1)
      MPI_Abort (MPI_COMM_WORLD, 123);
   orig_inst = num_instances;

   // Fila de espera inicia vazia
   for (int i = 0; i < n_procs-1; ++i) {
      waiting[i] = 0;
   }

   while (num_instances-- > 0) {
      int *x, *y;
      int last_i = 1, last_j = 2;
      char *path, *buffer;

      alive = n_procs-1;
      read_stdin(&x, &y);
      
      // Aloca vetor de path (caminho)
      init_tsp (x, y);
      path = calloc (nb_towns, sizeof(char));
      path[0] = 1;

      // Aloca buffer
      int buff_siz = sizeof(int) * 3 * nb_towns;
      buffer = malloc (buff_siz);
      memset (buffer, 0, buff_siz);

      int disp = (nb_towns-1)*(nb_towns-2);

      // Fila de espera inicia vazia
      for (int i = 0; i < n_procs-1; ++i) {
         if (waiting[i]) {
            disp--;
            MPI_Send (&nb_towns, 1, MPI_INT, i+1, NEW_WORK, MPI_COMM_WORLD);
            waiting[i] = 0;
         }
      }

      // Enquanto houverem trabalhadores ativos
      while (alive > 0) {
         MPI_Recv (&i_buff, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
         
         switch (status.MPI_TAG) {

            // Algum trabalhador quer iniciar, se houver o que calcular retorna positivamente, senao pede para o trabalhador encerrar
            case START:
               if (disp > 0) {
                  disp--;
                  if (i_buff == orig_inst-num_instances-1)
                     MPI_Send (&nb_towns, 1, MPI_INT, status.MPI_SOURCE, NEW_WORK, MPI_COMM_WORLD);
                  else
                     MPI_Send (&nb_towns, 1, MPI_INT, status.MPI_SOURCE, WORK, MPI_COMM_WORLD);
               }
               // Se for a ultima instancia, processo pode encerrar
               else if (num_instances == 0) {
                  MPI_Send (&nb_towns, 1, MPI_INT, status.MPI_SOURCE, END_WORK, MPI_COMM_WORLD);
                  alive--;
               }
               // Senao, processo entra na fila de espera para pegar a proxima
               else {
                  waiting[status.MPI_SOURCE-1] = 1;
                  alive--;
               }
               break;

            // Manda instancia nova para o processo
            case GET_INST:
               pos = 0;
               MPI_Pack (x, nb_towns, MPI_INT, buffer, buff_siz, &pos, MPI_COMM_WORLD);
               MPI_Pack (y, nb_towns, MPI_INT, buffer, buff_siz, &pos, MPI_COMM_WORLD);
               MPI_Send (buffer, buff_siz, MPI_PACKED, status.MPI_SOURCE, WORK, MPI_COMM_WORLD);
               break;

            // Manda caminho iniciando na proxima cidade
            case GET_WORK:
               pos = 0;
               MPI_Pack (&min_distance, 1, MPI_INT, buffer, buff_siz, &pos, MPI_COMM_WORLD);
               MPI_Pack (&last_j, 1, MPI_INT, buffer, buff_siz, &pos, MPI_COMM_WORLD);

               // Procura dist
               for (int i = 0; i < nb_towns; ++i) {
                  if (d_matrix[last_i][i].to_town == last_j)
                     dist = dist_to_origin[last_i] + d_matrix[last_i][i].dist;
               }

               MPI_Pack (&dist, 1, MPI_INT, buffer, buff_siz, &pos, MPI_COMM_WORLD);

               path[last_i] = 1;
               path[last_j] = 1;

               MPI_Pack (path, nb_towns, MPI_CHAR, buffer, buff_siz, &pos, MPI_COMM_WORLD);
               MPI_Send (buffer, buff_siz, MPI_PACKED, status.MPI_SOURCE, WORK, MPI_COMM_WORLD);

               path[last_i] = 0;
               path[last_j] = 0;

               // Não repete cidades
               if (last_j == last_i-1) last_j+=2;
               else last_j++;

               // Caso j chegue até a última, reinicia com i+1 e j = 1
               if (last_j >= nb_towns){
                  last_i++;
                  last_j = 1;
               }  

               break;
            
            case MIN_DIST:
               if (i_buff < min_distance)
                  min_distance = i_buff;
               break;

            default:
               break;
         }
      }

      printf ("%d ", min_distance);

      free (x);
      free (y);
      free (dist_to_origin);
      free (path);
      for (int i = 0; i < nb_towns; i++)
         free(d_matrix[i]);
      free(d_matrix);
      free (buffer);
   }
   printf ("\n");
}

void worker () {
   int *x, *y, buff_siz, old_towns = 0;
   char *path, *buffer;
   int inst = 0;

   while (1) {
      MPI_Send (&inst, 1, MPI_INT, 0, START, MPI_COMM_WORLD);
      MPI_Recv (&nb_towns, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

      if (status.MPI_TAG == NEW_WORK) {
         // Pede nova instancia
         MPI_Send (&inst, 1, MPI_INT, 0, GET_INST, MPI_COMM_WORLD);

         // Desaloca estruturas da instancia anterior
         if (inst != 0) {
            free (buffer);
            free (x);
            free (y);
            free (dist_to_origin);
            free (path);
            for (int i = 0; i < old_towns; i++)
               free(d_matrix[i]);
            free(d_matrix);
         }

         // Aloca buffer
         buff_siz = sizeof(int) * 3 * nb_towns;
         buffer = malloc (buff_siz);

         x = malloc(sizeof(int) * nb_towns);
         y = malloc(sizeof(int) * nb_towns);
         path = malloc (sizeof(char) * nb_towns);

         int pos = 0;
         MPI_Recv (buffer, buff_siz, MPI_PACKED, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
         MPI_Unpack (buffer, buff_siz, &pos, x, nb_towns, MPI_INT, MPI_COMM_WORLD);
         MPI_Unpack (buffer, buff_siz, &pos, y, nb_towns, MPI_INT, MPI_COMM_WORLD);

         init_tsp (x, y);
         inst++;
      }
      else if (status.MPI_TAG == END_WORK)
         break;

      int last, dist;
      MPI_Send (&inst, 1, MPI_INT, 0, GET_WORK, MPI_COMM_WORLD);

      int pos = 0;
      MPI_Recv (buffer, buff_siz, MPI_PACKED, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      MPI_Unpack (buffer, buff_siz, &pos, &min_distance, 1, MPI_INT, MPI_COMM_WORLD);
      MPI_Unpack (buffer, buff_siz, &pos, &last, 1, MPI_INT, MPI_COMM_WORLD);
      MPI_Unpack (buffer, buff_siz, &pos, &dist, 1, MPI_INT, MPI_COMM_WORLD);
      MPI_Unpack (buffer, buff_siz, &pos, path, nb_towns, MPI_CHAR, MPI_COMM_WORLD);

      tsp (3, dist, path, last);

      MPI_Send (&min_distance, 1, MPI_INT, 0, MIN_DIST, MPI_COMM_WORLD);

      old_towns = nb_towns;
   }

   free (x);
   free (y);
   free (dist_to_origin);
   free (path);
   free (buffer);
   for (int i = 0; i < nb_towns; i++)
      free(d_matrix[i]);
   free(d_matrix);
}

int main(int argc, char **argv)
{
   MPI_Init(&argc, &argv);
   int num_instances, st;
   int *x, *y;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

   double time = MPI_Wtime();

   if(rank == 0) manager();
   else worker();

   time = MPI_Wtime() - time;
   if(rank == 0) printf("Tempo total: %.15f\n", time);

   MPI_Finalize();
   return 0;
}
