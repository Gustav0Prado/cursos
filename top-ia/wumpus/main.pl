:- include(busca).
:- include(bc).
:- include(inicialbc).
:- include(def).
:- include(sat).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

wumpus_simplificado(N, Mapa) :-
    init_bc,
    inicial_BC(0, 0, N), !,
    busca(0, 0, Mapa, N, [], Caminho), %começa com caminho vazio []
    write(Caminho).
