program triangulo_nulo;
type
    matriz = array[1..50, 1..50] of integer;
var
    mat : matriz;
    n   : integer;

procedure leMat( var mat : matriz; n : integer );
var i, j : integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to n do
            read( mat[i, j] );
    end;
end;

function ehTriang( var mat : matriz; n : integer ) : boolean;
var i, j, somaC, somaB : integer;

begin
    somaC:= 0;
    somaB:= 0;
    for i:= 1 to n do
    begin
        for j:= i + 1 to n do
            somaC:= somaC + mat[i, j];
        for j:= 1 to i - 1 do
            somaB:= somaB + mat[i, j];
    end;
    if ( somaC = 0 ) OR ( somaB = 0 ) then
        ehTriang:= true
    else
        ehTriang:= false;
end;

begin
    read( n );
    leMat( mat, n );
    if ehTriang( mat, n ) then
        writeln( 'sim' )
    else
        writeln( 'nao' );
end.
