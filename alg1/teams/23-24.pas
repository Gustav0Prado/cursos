program matriz_media;
type
    matriz = array[1..50, 1..50] of real;
    vetor  = array[1..100] of real;
var
    mat : matriz;
    vet : vetor;
    n   : integer;
    m   : integer;

procedure leMat( var mat: matriz; n, m: integer );
var i, j: integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to m do
            read( mat[i, j] );
    end;
end;

procedure vetMedia( var mat: matriz; var vet: vetor; n, m: integer );
var i, j: integer;
    soma: real;

begin
    for j:= 1 to m do                       //de 1 ate m colunas
    begin
        soma:= 0;
        for i:= 1 to n do                   //de 1 ate n linhas
            soma:= soma + mat[i, j];        //soma elementos da coluna
        vet[j]:= soma/n;                    //guarda media da coluna no vetor
    end;
end;

procedure matMedia( var mat: matriz; var vet: vetor; n, m: integer );
var i, j: integer;

begin
    for j:= 1 to m do                               //de 1 ate m colunas
    begin
        for i:= 1 to n do                           //de 1 ate n linhas
            if mat[i, j] < vet[j] then              //altera os elementos a partir do
                mat[i, j]:= 0                       //vetor com as medias
            else
                mat[i, j]:= 1;
    end;
end;

procedure escVet( var vet: vetor; tam: integer );
var i: integer;

begin
    for i:= 1 to tam do                     //escreve vetor de 1 até tamanho
        write( vet[i]:0:2, ' ' );           //duas casas decimais
    writeln;
end;

procedure escMat( var mat: matriz; n, m: integer );
var i, j: integer;

begin
    for i:= 1 to n do                           //escreve mat a partir da linha 1
    begin
        for j:= 1 to m do                       //escreve mat a partir da coluna 1
            write( mat[i, j]:1:2, ' ' );        //escreve matriz espaçada/formatada com
        writeln;                                //duas casas decimais
    end;
end;

begin
    write( 'Insira as dimensões da matriz: ' );
    read( n, m );
    writeln;
    writeln( 'Insira a matriz: ' );
    leMat( mat, n, m );
    writeln;
    vetMedia( mat, vet, n, m );             //calcula vetor com as medias
    matMedia( mat, vet, n, m );             //modifica matriz
    escVet( vet, m );                       //escreve vetor com tamanho m
    escMat( mat, n, m );                    //escreve matriz n*m
end.
