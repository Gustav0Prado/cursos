program quadrado_magico_2;
type
    matriz = array[1..50, 1..50] of integer;
var
    mat : matriz;
    n   : integer;

procedure leMat( var mat: matriz; n: integer );
var i, j : integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to n do
            read( mat[i, j] );
    end;
end;

function temquad( var mat: matriz; i, j, n: integer ) : integer;
var tam, l, c, l1, c1, soma, nmag, cont, tammax: integer; ehquad: boolean;

begin
    cont:= 0;
    if ( n - i + 1 ) > ( n - j + 1 ) then
        tammax:= n - j + 1
    else
        tammax:= n - i + 1;
    for tam:= 2 to tammax do
    begin
        ehquad:= true;
        nmag:= 0;
        for l:= j to j + tam - 1 do
            nmag:= nmag + mat[1, l];
        for l:= i to i + tam - 1 do
        begin
            soma:= 0;
            for c:= j to j + tam - 1 do
                soma:= soma + mat[l, c];
            if soma <> nmag then
                ehquad:= false;
        end;
        for c1:= j to j + tam - 1 do
        begin
            soma:= 0;
            for l1:= i to i + tam - 1 do
                soma:= soma + mat[l1, c1];
            if soma <> nmag then
                ehquad:= false;
        end;
        if ehquad then
        begin
            writeln( tam, ' ', i, ' ', j );
            cont:= cont + 1;
        end;
    end;
    temquad:= cont;
end;

function quad( var mat: matriz; n: integer ) : integer;
var i, j, cont: integer;

begin
    cont:= 0;
    for i:= 1 to n do
    begin
        for j:= 1 to n do
           cont:= cont + temquad( mat, i, j, n );
    end;
    quad:= cont;
end;

procedure escMat( var mat: matriz; n: integer );
var i,j: integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to n do
            write( mat[i, j]:3, ' ' );
        writeln;
    end;
end;

begin
    read( n );
    leMat( mat, n );
    writeln( quad( mat, n ) );
    escMat( mat, n );
end.
