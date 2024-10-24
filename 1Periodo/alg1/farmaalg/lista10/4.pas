program quadrado_magico_1;
type
    matriz = array[1..50, 1..50] of integer;
var
    mat : matriz;
    n   : integer;

procedure leMat( var mat : matriz; n: integer );
var i, j : integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to n do
            read( mat[i, j] );
    end;
end;

function quad( var amt : matriz; n: integer ) : boolean;
var i, j, soma, nmag: integer;
    ehquad: boolean;

begin
    ehquad:= true;
    nmag:= 0;
    for j:= 1 to n do
        nmag:= nmag + mat[1, j];
    for i:= 1 to n do
    begin
        soma:= 0;
        for j:= 1 to n do
            soma:= soma + mat[i, j];
        if soma <> nmag then
            ehquad:= false;
    end;
    for j:= 1 to n do
    begin
        soma:= 0;
        for i:= 1 to n do
            soma:= soma + mat[i, j];
        if soma <> nmag then
            ehquad:= false;
    end;
    quad:= ehquad;
end;

begin
    read( n );
    leMat( mat, n );
    if quad( mat, n ) then
        writeln( 'sim' )
    else
        writeln( 'nao' );
end.
