program permutacoes_matriz;
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

function ehPerm( var mat: matriz; n: integer ) : boolean;
var i, k, cont: integer; permuta: boolean;

begin
    permuta:= true;
    for k:= 1 to n do
    begin
        cont:= 0;
        i:= 1;
        while ( i <= n ) and permuta do
        begin
            if ( mat[i, k] = 1 ) OR ( mat[k, i] = 1 ) then
                cont:= cont + 1
            else if ( ( mat[i, k] <> 0 ) OR ( mat[k, i] <> 0 ) ) AND ( ( mat[i, k] <> 1 ) OR ( mat[k, i] <> 1 ) ) then
                permuta:= false
            else if cont > 1 then
                permuta:= false;
            i:= i + 1;
        end;
    end;
    ehPerm:= permuta;
end;

begin
    read( n );
    leMat( mat, n );
    if ehPerm( mat, n ) then
        writeln( 'sim' )
    else
        writeln( 'nao' );
end.
