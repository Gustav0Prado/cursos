% consult(inicialbc).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

busca(I, J, Mapa, N, Caminho0, Caminho):-
    append(Caminho0, [[I, J]], Caminho1),
    anda(I, J, I1, J1, N),
    verifica_caminho(I1, J1, Caminho1),
    percebe(I1, J1, Mapa, X),
    reage(X, I1, J1, N, Caminho1),
    seguro(I1, J1, N),
    busca(I1, J1, Mapa, N, Caminho1, Caminho).

anda(I, J, I, J1, N):- J < N-1, J1 is J+1.  % anda para a direita
anda(I, J, I1, J, _):- I > 0, I1 is I-1.    % anda para cima
anda(I, J, I, J1, _):- J > 0, J1 is J-1.    % anda para a esquerda
anda(I, J, I1, J, N):- I < N-1, I1 is I+1.  % anda para baixo

verifica_caminho(I, J, Caminho):- not(member([I,J], Caminho)).  % Verifica se posicao I, J ainda NAO faz parte do caminho

reage(0, _, _, _, _).  % Detectou uma posicao vazia

reage(1, I, J, N, _):- % Detectou uma brisa
    brisa(I, J, N, Ind),
    C = [[Ind]],
    tell_bc(C), fail.

reage(2, I, J, _, Caminho):- % Detectou um poco
    append(Caminho, [[I, J]], Caminho1),
    write("Fim do Jogo, Caiu no poco!!!! Perdeu :("), nl,
    write("Caminho -> "),
    write(Caminho1), nl,
    halt.

reage(3, I, J, _, Caminho):- % Detectou ouro
    append(Caminho, [[I, J]], Caminho1),
    write("Fim do Jogo, Achou o ouro!!!! Ganhou :D"), nl,
    write("Caminho -> "),
    write(Caminho1), nl,
    halt.

seguro(I, J, N):- % Pergunta a BC se a posicao I, J eh segura
    poco(I, J, N, Ind),
    not(ask_bc(Ind)).