% consult(bc).
% consult(def).
:- style_check(-singleton).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% define a BC inicial recursivamente
inicial_BC(I, J, N) :-
    proximo(I, J, N, I1, J1),
    regras(I, J, N),
    inicial_BC(I1, J1, N).

inicial_BC(I, J, N) :-
    regras(I, J, N).
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% forma elegante de percorrer toda a matriz
proximo(I, J, N, I1, J) :-
    I < N-1,
    I1 is I+1.

proximo(_, J, N, 0, J1) :-
    J < N-1,
    J1 is J+1.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% inclui na BC as regras do jogo para a posição (I,J)
regras(I, J, N) :-
    I > 0, I < N-1,
    J > 0, J < N-1,
    I1 is I-1,
    I2 is I+1,
    J1 is J-1,
    J2 is J+1,
    brisa(I, J, N, Ind),  MInd is -Ind,
    poco(I1, J, N, Ind1), MInd1 is -Ind1,
    poco(I2, J, N, Ind2), MInd2 is -Ind2,
    poco(I, J1, N, Ind3), MInd3 is -Ind3,
    poco(I, J2, N, Ind4), MInd4 is -Ind4,
    C = [[MInd, Ind1, Ind2, Ind3, Ind4],
         [MInd1, Ind], [Mind2, Ind],
         [MInd3, Ind], [Mind4, Ind]],
    tell_bc(C).

% regras(I, J, N). %implementar casos de borda

%casos de borda
% primeira linha
regras(I, J, N) :-
    I is 0,
    J > 0, J < N-1,
    I2 is I+1,
    J1 is J-1,
    J2 is J+1,
    brisa(I, J, N, Ind),  MInd is -Ind,
    poco(I2, J, N, Ind2), MInd2 is -Ind2,
    poco(I, J1, N, Ind3), MInd3 is -Ind3,
    poco(I, J2, N, Ind4), MInd4 is -Ind4,
    C = [[MInd, Ind2, Ind3, Ind4], [Mind2, Ind],[MInd3, Ind], [Mind4, Ind]],
    tell_bc(C).

% ultima linha
regras(I, J, N) :-
    I is N-1,
    J > 0, J < N-1,
    I1 is I-1,
    J1 is J-1,
    J2 is J+1,
    brisa(I, J, N, Ind),  MInd is -Ind,
    poco(I1, J, N, Ind1), MInd1 is -Ind1,
    poco(I, J1, N, Ind3), MInd3 is -Ind3,
    poco(I, J2, N, Ind4), MInd4 is -Ind4,
    C = [[MInd, Ind1, Ind3, Ind4], [MInd1, Ind], [MInd3, Ind], [Mind4, Ind]],
    tell_bc(C).

% primeira coluna
regras(I, J, N) :-
    I > 0, I < N-1,
    J is 0,
    I1 is I-1,
    I2 is I+1,
    J2 is J+1,
    brisa(I, J, N, Ind),  MInd is -Ind,
    poco(I1, J, N, Ind1), MInd1 is -Ind1,
    poco(I2, J, N, Ind2), MInd2 is -Ind2,
    poco(I, J2, N, Ind4), MInd4 is -Ind4,
    C = [[MInd, Ind1, Ind2, Ind4], [MInd1, Ind], [Mind2, Ind], [Mind4, Ind]],
    tell_bc(C).

% ultima coluna
regras(I, J, N) :-
    I > 0, I < N-1,
    J is N-1,
    I1 is I-1,
    I2 is I+1,
    J1 is J-1,
    brisa(I, J, N, Ind),  MInd is -Ind,
    poco(I1, J, N, Ind1), MInd1 is -Ind1,
    poco(I2, J, N, Ind2), MInd2 is -Ind2,
    poco(I, J1, N, Ind3), MInd3 is -Ind3,
    C = [[MInd, Ind1, Ind2, Ind3], [MInd1, Ind], [Mind2, Ind], [MInd3, Ind]],
    tell_bc(C).

% esquerda superior
regras(I, J, N) :-
    I is 0,
    J is 0,
    I2 is I+1,
    J2 is J+1,
    brisa(I, J, N, Ind),  MInd is -Ind,
    poco(I2, J, N, Ind2), MInd2 is -Ind2,
    poco(I, J2, N, Ind4), MInd4 is -Ind4,
    C = [[MInd, Ind2, Ind4], [Mind2, Ind], [Mind4, Ind]],
    tell_bc(C).

% direita superior
regras(I, J, N) :-
    I is 0,
    J is N-1,
    I2 is I+1,
    J1 is J-1,
    brisa(I, J, N, Ind),  MInd is -Ind,
    poco(I2, J, N, Ind2), MInd2 is -Ind2,
    poco(I, J1, N, Ind3), MInd3 is -Ind3,
    C = [[MInd, Ind2, Ind3], [Mind2, Ind], [MInd3, Ind]],
    tell_bc(C).

% esquerda inferior
regras(I, J, N) :-
    I is N-1,
    J is 0,
    I1 is I-1,
    J2 is J+1,
    brisa(I, J, N, Ind),  MInd is -Ind,
    poco(I1, J, N, Ind1), MInd1 is -Ind1,
    poco(I, J2, N, Ind4), MInd4 is -Ind4,
    C = [[MInd, Ind1, Ind4], [MInd1, Ind], [Mind4, Ind]],
    tell_bc(C).

% direita inferior
regras(I, J, N) :-
    I is N-1,
    J is N-1,
    I1 is I-1,
    J1 is J-1,
    brisa(I, J, N, Ind),  MInd is -Ind,
    poco(I1, J, N, Ind1), MInd1 is -Ind1,
    poco(I, J1, N, Ind3), MInd3 is -Ind3,
    C = [[MInd, Ind1, Ind3], [MInd1, Ind],[MInd3, Ind]],
    tell_bc(C).
