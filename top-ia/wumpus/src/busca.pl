% consult(inicialbc).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

busca(I, J, Mapa, _, Caminho0, Caminho1):-
    append(Caminho0, [[I, J]], Caminho1),
    percebe(I, J, Mapa, X),
    X is 3,
    true.

busca(I, J, Mapa, _, Caminho0, Caminho1):-
    append(Caminho0, [[I, J]], Caminho1),
    percebe(I, J, Mapa, X),
    X is 2,
    write("Caiu no poco, perdeu o jogo :("), nl,
    write("Caminho -> "), write(Caminho1), nl,
    halt.

busca(I, J, Mapa, N, _, _):-
    % coloca brisa na BC
    percebe(I, J, Mapa, X),
    X is 1,
    brisa(I, J, N, Ind),
    C = [[Ind]],
    tell_bc(C),
    fail.

busca(I, J, Mapa, N, Caminho0, Caminho):-
    percebe(I, J, Mapa, X),
    X is 0,
    append(Caminho0, [[I, J]], Caminho1),
    anda(I, J, I1, J1, N),
    verifica_caminho(I1, J1, Caminho1),
    seguro(I1, J1, N),
    busca(I1, J1, Mapa, N, Caminho1, Caminho).

anda(I, J, I, J1, N):- J < N-1, J1 is J+1.  % anda para a direita
anda(I, J, I1, J, _):- I > 0,   I1 is I-1.  % anda para cima
anda(I, J, I, J1, _):- J > 0,   J1 is J-1.  % anda para a esquerda
anda(I, J, I1, J, N):- I < N-1, I1 is I+1.  % anda para baixo

verifica_caminho(I, J, Caminho):- not(member([I,J], Caminho)).  % Verifica se posicao I, J ainda NAO faz parte do caminho

seguro(I, J, N):- % Pergunta a BC se a posicao I, J eh segura (sem poço)
    poco(I, J, N, Ind),
    not(ask_bc(Ind)).