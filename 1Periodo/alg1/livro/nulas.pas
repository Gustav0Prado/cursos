program linhas_colunas_nulas;
type
    matriz = Array[1..50, 1..50] of integer;
var
    mat : matriz;
    n   : integer;
    m   : integer;

procedure leMat( var mat : matriz; n, m : integer );
var i, j : integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to m do
            read( mat[i, j] );
    end;
end;

function linNul( var mat : matriz; n, m : integer ) : integer;
var i, j, cont, soma : integer;

begin
    cont:= 0;
    for i:= 1 to n do
    begin
        soma:= 0;
        for j:= 1 to m do
            soma:= soma + mat[i, j];
        if soma = 0 then
            cont:= cont + 1;
    end;
    linNul:= cont;
end;

function colNul( var mat : matriz; n, m : integer ) : integer;
var i, j, cont, soma : integer;

begin
    cont:= 0;
    for j:= 1 to m do
    begin
        soma:= 0;
        for i:= 1 to n do
            soma:= soma + mat[i, j];
        if soma = 0 then
            cont:= cont + 1;
    end;
    colNul:= cont;
end;

begin
    read( n, m );
    leMat( mat, n, m );
    writeln( linNul( mat, n, m ), ' ', colNul( mat, n, m ) );
end.
