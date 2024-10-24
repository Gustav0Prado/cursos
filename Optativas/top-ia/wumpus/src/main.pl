:- include(busca).
:- include(bc).
:- include(inicialbc).
:- include(def).
:- include(sat).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

ganhou(Caminho):-
    write("Achou o ouro, ganhou :)"),
    nl,
    write("Caminho -> "),
    write(Caminho),
    nl.

wumpus_simplificado(N, Mapa) :-
    init_bc,
    inicial_BC(0, 0, N), !,
    ( busca(0, 0, Mapa, N, [], Caminho), ! -> ganhou(Caminho); write("Nao achou ouro, mapa impossivel :|"), nl).
    % Caso queira so o resultado da busca em si:
    % busca(0, 0, Mapa, N, [], Caminho), !.
    