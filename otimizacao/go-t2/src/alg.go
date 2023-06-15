package main

// Função de Backtracking, ou seja, com corte de viabilidade mas sem corte de otimalidade
func Backtrack(choices []Hero, left []Hero, right []Hero, l int, n int) {
	nodes++

	if l == n {
		c := num_conlicts(left, right)
		if c < optConf {
			optConf = c
			optLeft = left
			optRight = right
		}
		return

	} else {
		next := choices[0]
		if len(left) < n-1 && (has_affinities(left, next) || !has_affinities(right, next)) {
			Backtrack(choices[1:], append(left, next), right, l+1, n)
		}
		if len(right) < n-1 && (has_affinities(right, next) || !has_affinities(left, next)) {
			Backtrack(choices[1:], left, append(right, next), l+1, n)
		}
	}

}

// Função de enumeração, ou seja, sem corte de viabilidade
func Enumerate(choices []Hero, left []Hero, right []Hero, l int, n int) {
	nodes++

	if l == n {
		c := num_conlicts(left, right)
		if c < optConf {
			optConf = c
			optLeft = left
			optRight = right
		}
		return

	} else {
		next := choices[0]
		Enumerate(choices[1:], append(left, next), right, l+1, n)
		Enumerate(choices[1:], left, append(right, next), l+1, n)
	}

}

func BranchAndBound() {

}
