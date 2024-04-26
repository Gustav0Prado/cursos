
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% definicao de indice da brisa
brisa(I, J, N, Ind) :-
    Ind is I*N+J+1.

% definicao de indice do poco
poco(I, J, N, Ind) :-
    Ind is N*N+I*N+J+1.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% percepcao na posicao (I,J)
percebe(I, J, Mapa, X) :- 
    nth0(I, Mapa, LI), 
    nth0(J, LI, X).
