program palavra_cruzada;
type
    matriz = array[1..50, 1..50] of integer;
var
    mat : matriz;
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

function pode( var mat: matriz; i, j, n, m: integer ): boolean;
var minCol, minLin, maxLin: integer; podeserl, podeserc: boolean;

begin
    podeserc:= false;
    podeserl:= false;
    if j = 1 then
        minCol:= j
    else if j = m then
        minCol:= j - 1
    else
        minCol:= j - 1;
    if i = 1 then
    begin
        maxLin:= i + 1;
        minLin:= i;
    end
    else if i = n then
    begin
        maxLin:= i;
        minLin:= i - 1;
    end
    else
    begin
        maxLin:= i + 1;
        minLin:= i - 1;
    end;
    if ( ( mat[i, minCol] = -1 ) AND ( j + 1 <= m ) ) OR ( j = 1 ) then
        podeserl:= true;
    if ( ( mat[minLin, j] = -1 ) AND ( i + 1 <= n ) AND ( mat[maxLin, j] = 0 ) ) OR ( i = 1 ) then
        podeserc:= true;
    if podeserl OR podeserc then
        pode:= true
    else
        pode:= false;
end;

procedure cruzada( var mat: matriz; n, m: integer );
var i, j, cont: integer;

begin
    cont:= 1;
    for i:= 1 to n do
    begin
        for j:= 1 to m do
        begin
            if mat[i, j] = 0 then
            begin
                if pode( mat, i, j, n, m ) then
                begin
                    mat[i, j]:= cont;
                    cont:= cont + 1;
                end;
            end;
        end;
    end;
end;

procedure escMat( var mat: matriz; n, m: integer );
var i, j: integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to m do
            write( mat[i, j]:3, ' ' );
        writeln;
    end;
end;

begin
    read( n, m );
    leMat( mat, n, m );
    cruzada( mat, n, m );
    writeln;
    escMat( mat, n, m );
end.
