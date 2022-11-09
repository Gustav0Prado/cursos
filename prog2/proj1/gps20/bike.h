/* Gustavo do Prado Siva
   GRR20203942*/

#include <dirent.h>
#include <sys/types.h>

/*define limites para: nome do modelo de uma bike, numero de bikes e de logs antes de realocar
 e numero de chars em uma linha*/
#define TAMNOME 50
#define NLOGS 30
#define LSIZE 49

/*Define estrutura de um registro de uma bicicleta*/
typedef struct RegBike{
   int Dia;
   int Mes;
   int HRmax;
   double Distancia;
   double VelocidadeMed;
   double VelocidadeMax;
   double SubidaAcum;
   double HRmedio;
   double Cadencia;
} t_LogBike;

/*estrutura da bicleta em si*/
typedef struct Bike{
   char Modelo[TAMNOME];
   t_LogBike *VetorLog;
   struct Bike *prox;
   double pedalC;
   double pedalL;
   double distT;
   int tam;
   int max;
} t_Bike;

typedef struct Lista{
   t_Bike *ini;
   t_Bike *fim;
   int numLog;
} t_ListaBike;

/*struct para guardar infos dos timestamps*/
typedef struct hora{
   int ini;
   int atual;
   int ult;
   
} t_Hora;

/*struct para guardar infos das medias*/
typedef struct media{
   double atual;
   double media;
   double peso;
   double ult;
} t_Media;

/*verifica se eh um arquivo com extensao log*/
int ehlog(int tipo, char* nome);

/*retorna se log eh invalido*/
int logInvalido(FILE* arq);

/*aloca lista caso seja nula ou cria e insere no se ja existir*/
t_Bike *aloca(t_ListaBike **lista, FILE *arq);

/*cria um no dado um modelo de bike*/
t_Bike *criaNo(char *modelo);

/*insere um no no final da lista*/
int insereNo(t_Bike *no, t_ListaBike *lista);

/*le arquivos de um diretorio e guarda informacoes numa lista de bikes*/
t_ListaBike *leDir(DIR *dirlog, char *argv);

/*zera todos os valores de um log do vetor*/
void zeraLog(t_Bike *aux, int posLog);

/*calcula maior pedal, menor pedal e distancia total de uma bike*/
int calculaInfos(t_Bike *aux, int plog);

/*da free nos ponteiros das estruturas*/
int desaloca(t_ListaBike *lista);