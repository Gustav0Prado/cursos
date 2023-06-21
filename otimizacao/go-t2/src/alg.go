package main

/*
Função de Backtracking, ou seja, sem corte de otimalidade

choices = lista com herois ainda nao escolhidos
left  = primerio grupo de herois
right = segundo grupo de herois
n = numero de herois a ser escolhidos ainda
*/
func Backtrack(choices []Hero, left []Hero, right []Hero, n int) {
	nodes++

	//Todos os herois já foram escolhidos
	if n == 0 {
		c := num_conlicts(left, right)
		if c < optConf {
			optConf = c
			optLeft = left
			optRight = right
		}
		return

	} else {
		next := choices[0]

		/* Apenas ramifica se:
		1. O outro lado não for ficar vazio
		2. Se tiver afinidade com alguem do grupo
		3. Se tiver espaco no grupo e não tiver afinidade com ninguem do outro grupo
		*/

		if len(left) <= n && (has_affinities(left, next) || !has_affinities(right, next)) {
			Backtrack(choices[1:], append(left, next), right, n-1)
		}
		if len(right) <= n && (has_affinities(right, next) || !has_affinities(left, next)) {
			Backtrack(choices[1:], left, append(right, next), n-1)
		}
	}

}

/*
Função de enumeração, ou seja, sem corte de viabilidade
choices = lista com herois ainda nao escolhidos
left  = primerio grupo de herois
right = segundo grupo de herois
n = numero de herois a ser escolhidos ainda
*/
func Enumerate(choices []Hero, left []Hero, right []Hero, n int) {
	nodes++

	// Todos os herois ja foram escolhidos
	if n == 0 {
		c := num_conlicts(left, right)
		if c < optConf {
			optConf = c
			optLeft = left
			optRight = right
		}
		return

	} else {
		next := choices[0]
		Enumerate(choices[1:], append(left, next), right, n-1)
		Enumerate(choices[1:], left, append(right, next), n-1)
	}

}

func BranchAndBound() {

}
