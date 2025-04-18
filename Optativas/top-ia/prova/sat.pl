satL(L, V, V) :-
   member(L, V), !.

satL(L, V0, V) :-
   L1 is -L,
   not(member(L1, V0)),
   append(V0, [L], V).

satC([L|_], V0, V) :-
   satL(L, V0, V).

satC([_|C], V0, V) :-
   satC(C, V0, V).

sat([], V, V).

sat([C|F], V0, V) :-
   sat(F, V0, V1),
   satC(C, V1, V).