program ampulheta_soma;
type
    matriz = array[1..50, 1..50] of integer;
var 
    mat   : matriz;
    n     : integer;
    i     : integer;
    j     : integer;
    msoma : integer;
    soma  : integer;

procedure leMat( var mat : matriz; n : integer );
var i, j: integer;

begin
    for i := 1 to n do
    begin
        for j := 1 to n do
            read( mat[i ,j] );
    end;
end;

function somaAmp(var mat: matriz; lin, col: integer ): integer;
var soma, j: integer;

begin
    soma:= 0;
    for j:= col to col + 2 do
        soma:= soma + mat[lin, j];
    for j:= col to col + 2 do
        soma:= soma + mat[lin + 2, j];
    soma:= soma + mat[lin + 1, col + 1];
    somaAmp:= soma;
end;

begin
    read( n );
    leMat( mat, n );
    msoma:= 0;
    soma:= 0;
    for i:= 1 to n - 2 do
    begin
        for j:= 1 to n - 2 do
        begin
            soma:= somaAmp( mat, i, j );
            if ( soma > msoma ) then
                msoma:= soma;
        end;
    end;
    writeln( msoma ); 
end.