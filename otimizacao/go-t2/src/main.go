package main

import (
	"fmt"
	"os"
	"strings"
)

var optLeft, optRight []Hero
var optConf = 1000
var nodes = 0

func main() {
	var n, k, m int
	var choices, left, right []Hero

	// Lê da entrada padrão
	fmt.Scan(&n, &k, &m)

	// Inicializa n heróis com ids de 1 a n
	for i := 0; i < n; i++ {
		choices = append(choices, Hero{id: i + 1})
	}

	// Lê conflitos
	for i := 0; i < k; i++ {
		var h, c int
		fmt.Scan(&h, &c)
		choices[h-1].conflicts = append(choices[h-1].conflicts, c)
	}

	// Lê afinidades
	for i := 0; i < m; i++ {
		var h, a int
		fmt.Scan(&h, &a)
		choices[h-1].affinities = append(choices[h-1].affinities, a)
	}

	// Executa programa de acordo com as opções da linha de comando
	if len(os.Args) > 1 {
		switch os.Args[1] {
		case "-f":
			Enumerate(choices, left, right, 0, n)

		case "-o":
			Backtrack(choices, left, right, 0, n)

		case "-a":
			fmt.Println("Função dada")

		default:
			fmt.Printf("Opção não encontrada.\n")
			fmt.Printf("Opções disponíveis:\n\t-a (Função dada)\n\t-f (Sem cortes de viabilidade)\n\t-o (Sem cortes de optimalidade)\n\tsem opções (Programa padrão)\n")
		}
	} else {
		fmt.Println("Programa padrão")
	}

	fmt.Println(optConf)
	if contains(optLeft, nil, 1) {
		fmt.Println(strings.Trim(fmt.Sprint(optLeft), "[]"))
	} else {
		fmt.Println(strings.Trim(fmt.Sprint(optRight), "[]"))
	}
	fmt.Fprintln(os.Stderr, nodes, "nós na árvore")

}
