program maxPool;
type
    matriz = array[1..50, 1..50] of integer;
var 
    mat : matriz;
    res : matriz;
    n   : integer;
    p   : integer;
    i   : integer;
    j   : integer;
    linR: integer;
    colR: integer;

procedure leMat( var mat: matriz; n: integer );
var i, j: integer;

begin
    for i := 1 to n do
    begin
        for j := 1 to n do
            read( mat[i, j] );
    end;
end;

procedure pool( var mat, res: matriz; i, j, p, linR, colR: integer );
var 
    lin, col, maior, elem: integer;

begin
    maior:= 0;
    for lin:= i to i + 2 - 1 do
    begin
        for col:= j to j + 2 - 1 do
        begin
            elem:= mat[lin, col];
            if elem > maior then
                maior:= elem;
        end;
    end;
    res[linR, colR]:= maior;
end;

procedure escMat( var mat: matriz );
var i, j: integer;

begin
    for i := 1 to n - p do
    begin
        for j:= 1 to n - p do
            write( mat[i, j]:3, ' ' );
        writeln;
    end;
end;

begin
    read( n, p );
    leMat( mat, n );
    i:= 1;
    j:= 1;
    linR:= 1;
    while i <= n - 1 do
    begin
        colR:= 1;
        while j <= n - 1 do
        begin
            pool( mat, res, i, j, p, linR, colR );
            j:= j + p;
            colR:= colR + 1;
        end;   
        i:= i + p;
        j:= 1;
        linR:= linR + 1;
    end;
    writeln;
    escMat( res );
end.