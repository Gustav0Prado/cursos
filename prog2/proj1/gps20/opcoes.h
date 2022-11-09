/* Gustavo do Prado Siva
   GRR20203942*/

/*imprime a tabela de opcoes*/
void imprimeOpcoes();

/*funcao para imprimir dados do vetor para o histograma*/
int histograma(t_Bike vet[], int tam, double pedalCurto, double pedalLongo);

/*imprime todos os modelos de bicicletas encontrados*/
int opcao1(t_ListaBike *lista);

/*imprime atividades de uma bicicleta específica*/
int opcao2(t_ListaBike *lista);

/*ordena por data e depois imprime as atividades agrupadas por bicicleta*/
int opcao3(t_ListaBike *lista);

/*ordena por distancia e depois imprime as atividades agrupadas por bicicleta*/
int opcao4(t_ListaBike *lista);

/*ordena todas as atividades por subida acumulada e depois as imprime*/
int opcao5(t_ListaBike *lista, int numlog);

/*cria histograma com as distancias de cada bicicleta e o mostra na tela*/
int opcao6(t_ListaBike *lista);