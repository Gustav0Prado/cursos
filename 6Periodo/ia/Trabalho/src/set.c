/**
 * Função que gera recursivamente os subconjuntos de tamanho r e aplica neles uma função f
 */
void generate_subsets(int *set, int n, int r, int *temp, int index, int i, void (*f)(int *subset)){
    if (index == r) {
        f(temp);
    }

    if (i >= n) return;

    temp[index] = set[i];
    create_subsets(set, n, r, temp, index+1, i+1, f);
    create_subsets(set, n, r, temp, index  , i+1, f);
}