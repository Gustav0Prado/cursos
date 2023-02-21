MATRIZ ORIGINAL:

Original

1   2   0   0   0
3   4   5   0   0
0   6   7   8   0
0   0   9  10  11
0   0   0  12  13


Transposta

1   3   0   0   0
2   4   6   0   0
0   5   7   9   0
0   0   8  10  12
0   0   0  11  13


Para guardar a matriz original, ao invés de utilizar uma matriz n*n, utilizamos um vetor k*n, 
que armazena apenas as diagonais da matriz. Consequentemente a transposta será n*k, e ambas seguem a seguinte forma:

Diagonal
 0    1    2
 3    4    5
 6    7    8
 9   10   11
12   13    0



Transposta
 0    3    6    9   12
 1    4    7   10   13
 2    5    8   11    0


A matriz diagonal original fica salva na struct do sistema linear, em outra struct MatDiag_t que possui:
* Vetor n*k (A)
* B original (b)
* Vetor com posições de início originais das linhas (jstart)
* Vetor com posições de fim originais das linhas (jend)

Os dois vetores servem para saber quando começar a multiplicar a linha, já que originalmente quanto mais para baixo 
mais elas estariam deslocadas e começariam em 0. 
Então ao invés de começarmos sempre a multiplicar os valores a partir da posição 0 começamos em jstart (posição do primeiro não nulo).
Do mesmo jeito é jend, mas com as posições em que as linhas acabam.
(Ainda não achei um jeito decente de fazer as operações de resíduo e multiplicação da transposta usando somente os índices,
estou usando uma função que pega da matriz, o que não é muito bom pro desempenho)

MATRIZ SIMÉTRICA:

Original:

1   2   3    0   0
2   4   5    6   0
3   5   7    8   9
0   6   8   10  11
0   0   9   11  12

Alterada:

 1     2   3 
 4     5   6
 7     8   9
10    11   x
12     x   x

Possui k linhas de tamanho k e depois elas vão diminuindo até o tamanho 1.
Guarda apenas da diagonal principal para cima, sem nenhum zero
A matriz simétrica fica salva na struct do sistema linear, em outra struct MarSim_t que possui:
* Vetor de tamanho (n*k) + (k*k-k))/2 (A)
* B original (b)
* Vetor com posições de início originais das linhas (jstart)
* Vetor com posições de fim originais das linhas (jend)

(Obs: estou pensando em simplificar e transformar em uma matriz n*k também, pra não ficar esse tamanho variável confuso)

As operações que precisaram ser alteradas foram: transposição e multiplicação pela transposta,
multiplicação de matriz por vetor (foi adicionada a função multMatSimVet) e
o cálculo do resíduo com a matriz diagonal (adicionada a função calcResiduo).

Motivo: Matrizes de tamanho grande tinham muitas posições de memória ocupadas mesmo sem utilizar, já que eram ocupadas por 0s
dessa maneira temos bem uso de memória e um tempo menor de execução já que os laços são menores e os cálculos ocorrem menos vezes.
Por exemplo, para n = 8000 e k = 7, na versão 1 teríamos 64.000.000 posições de memória (8000 x 8000) enquanto na versão 2 temos
56021 posições (8000x7 + (7*7-7)/2)


para printar as matrizes coloquei prnSisLinDiag (Diagonal/Original) e prnSisLinSim (simetrica/Alterada), ta meio feio mas funciona

para plotar os graficos usar ./saida/plotAlgumaCoisa (L3,Tempo,etc) depois de rodar o script