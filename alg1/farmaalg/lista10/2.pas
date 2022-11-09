program odeio_equacoes;
type
    matriz = array[1..50, 1..50] of real;
    vetor = array[1..100] of real;
var
    mat    : matriz;
    inres  : vetor;
    res    : vetor;
    ldir   : vetor;
    n      : integer;
    m      : integer;

procedure leMat( var mat: matriz; n, m: integer );
var i, j: integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to m do
            read( mat[i, j] );
    end;
end;

procedure leVet( var vet: vetor );
var i : integer;

begin
    for i:= 1 to n do
        read( vet[i] );
end;

procedure multiplica( var matrix: matriz; n, m: integer; var vet, res: vetor );
var i,j: integer; soma: real;

begin
    for i:= 1 to n do
    begin
        soma:= 0;
        for j:= 1 to m do
            soma:= soma + matrix[i, j] * vet[j];
        res[i]:= soma;
    end;
end;

function igual( var vet1, vet2 : vetor ) : boolean;
var i: integer; iguais: boolean;

begin
    iguais:= true;
    for i:= 1 to n do
    begin
        if vet1[i] <> vet2[i] then
            iguais:= false;
    end;
    igual:= iguais;
end;

begin
    read( n, m );
    leVet( inres );
    leMat( mat, n, m );
    leVet( ldir );
    multiplica( mat, n, m, inres, res );
    if igual( res, ldir ) then
        writeln( 'sim' )
    else
        writeln( 'nao' );
end.
