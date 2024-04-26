
% predicados para gerenciar a BC
%
% init_bc     inicializa a BC. Chamar antes de tudo.
%
% tell_bc(LC) inclui uma lista de cláusulas na BC.
%             Se apenas um literal for incluído:
%             tell_bc([[L]]).
%
% ask_bc(L)   TRUE se o literal L for consequência
%             lógica da BC
%
% Obs: para otimizar a BC, sempre que um único literal
%      for incluído, BCP (Binary Constraint Propagation)
%      é usado para propagar o seu valor-verdade ao invés
%      de incluí-lo de fato na BC. Isso melhora o desempenho
%      do predicado sat\3 chamado internamente.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% consult(sat).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

bcp(_, [], []).

bcp(L, [C|Cs], Cs1) :-
    bcpl(L, C, []),!,
    bcp(L, Cs, Cs1).

bcp(L, [C|Cs], [C1|Cs1]) :-
    bcpl(L, C, C1),
    bcp(L, Cs, Cs1).

bcpl(L, C, C) :-
    not(member(L, C)),
    L1 is -L,
    not(member(L1, C)).

bcpl(L, C, []) :-
    member(L, C).

bcpl(L, C, C1) :-
    L1 is -L,
    member(L1, C),
    subtract(C, [L1], C1),
    not(C1 = []).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

init_bc :-
    nb_setval(bc, []).

tell_bc([[L]]) :- !,
    nb_getval(bc, BC),
    bcp(L, BC, BC1),
    nb_setval(bc, BC1).

tell_bc(LC) :-
    nb_getval(bc, BC),
    append(BC, LC, BC1),
    nb_setval(bc, BC1).

ask_bc(L) :-
    nb_getval(bc, BC),
    L1 is -L,
    not(bcp(L1, BC, _)).
    
ask_bc(L) :-
    nb_getval(bc, BC),
    L1 is -L,
    bcp(L1, BC, BC1),
    not(sat(BC1,[],_)).

write_bc :-
    nb_getval(bc, BC),
    write(BC).
