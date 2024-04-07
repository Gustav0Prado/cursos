analisa_formula([H|TAIL], V) :-
    analisa_clausula(H, V),
    analisa_formula(TAIL, V).

analisa_formula([], _) :- true.

analisa_clausula([T|TAIL], V) :-
    T > 0,
    nth1(T, V, Valor),
    Valor is 1; analisa_clausula(TAIL, V).

analisa_clausula([T|TAIL], V) :-
    T is -T,
    nth1(T, V, Valor),
    Valor is 0; analisa_clausula(TAIL, V).

analisa_clausula([], _) :- false.
