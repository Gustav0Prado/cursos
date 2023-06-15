package main

import "fmt"

type Hero struct {
	id         int
	affinities []int
	conflicts  []int
}

// Retorna id do herói para a função print
func (h Hero) String() string {
	return fmt.Sprintf("%d", h.id)
}

// Retorna se um dado herói esta presente em uma lista/time
func contains(listHero []Hero, listInt []int, hero int) bool {
	// Lista tem tipo Hero
	if listInt == nil {
		for _, h := range listHero {
			if h.id == hero {
				return true
			}
		}

		// Lista tem tipo Int
	} else if listHero == nil {
		for _, h := range listInt {
			if h == hero {
				return true
			}
		}
	}

	return false
}

// Retorna número total de conflitos em ambas as equipes
func num_conlicts(left []Hero, right []Hero) int {
	conflicts := 0

	// Conflitos no grupo esquerdo
	for _, h := range left {
		for _, c := range h.conflicts {
			if contains(left, nil, c) {
				conflicts++
			}
		}
	}

	// Conflitos no grupo direito
	for _, h := range right {
		for _, c := range h.conflicts {
			if contains(right, nil, c) {
				conflicts++
			}
		}
	}

	return conflicts
}

// Retorna se um certo herói tem afinidade com algúem de certo grupo
func has_affinities(team []Hero, hero Hero) bool {
	for _, h := range team {
		if contains(nil, h.affinities, hero.id) {
			return true
		}
	}
	return false
}
