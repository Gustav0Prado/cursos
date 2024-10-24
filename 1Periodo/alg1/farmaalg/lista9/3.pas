program repeticao_matriz;
type
    matriz = Array[1..50, 1..50] of integer;
var
    mat : matriz;
    m   : integer;
    n   : integer;

procedure leMat( var mat : matriz; n, m : integer );
var i, j : integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to m do
            read( mat[i, j] );
    end;
end;

function tem( num : integer; var mat : matriz; n, m : integer ) : boolean;
var i, j, cont : integer;

begin
    cont:= 0;
    for i:= 1 to n do
    begin
        for j:= 1 to m do
        begin
            if num = mat[i, j] then
                cont:= cont + 1;
        end;
    end;
    if cont > 1 then
        tem:= true
    else
        tem:= false;
end;

function repete( var mat : matriz; n, m : integer ) : boolean;
var i, j : integer; repetido: boolean;

begin
    repetido:= false;
    for i:= 1 to n do
    begin
        for j:= 1 to m do
        begin
            if tem(mat[i, j], mat, n, m ) then
                repetido:= true;
        end;
    end;
    repete:= repetido;
end;

begin
    read( n, m );
    leMat( mat, n, m );
    if repete( mat, n, m ) then
        writeln( 'sim' )
    else
        writeln( 'nao' );
end.
