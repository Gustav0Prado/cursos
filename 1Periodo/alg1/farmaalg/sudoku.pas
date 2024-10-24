program sudoku_doido;
const
    LIN = 9;
    COL = 9;
type
    matriz = array[1..LIN, 1..LIN] of integer;
var
    mat : matriz;

procedure leMat( var mat : matriz );
var i, j : integer;

begin
    for i:= 1 to LIN do
    begin
        for j:= 1 to COL do
            read( mat[i, j] );
    end;
end;

procedure minmax( n, m : integer; var minl, maxl, minc, maxc : integer );
begin

    if n <= 3 then
    begin
        minl:= 1;
        maxl:= 3;
    end
    else if n > 3 then
    begin
        minl:= 4;
        maxl:= 6;
    end
    else if n > 6 then
    begin
        minl:= 7;
        maxl:= 9;
    end;
    if m <= 3 then
    begin
        minc:= 1;
        maxc:= 3;
    end
    else if m > 3 then
    begin
        minc:= 4;
        maxc:= 6;
    end
    else if m > 6 then
    begin
        minc:= 7;
        maxc:= 9;
    end;
end;

function tem( var mat : matriz; num, n, m : integer ) : boolean;
var i, j, maxl, maxc, minl, minc, achou : integer;

begin
    achou:= 0;
    for i:= n + 1 to LIN do
    begin
        if mat[i, m] = num then
            achou:= achou + 1;
    end;
    for j:= m + 1 to COL do
    begin
        if mat[n, j] = num then
            achou:= achou + 1;
    end;
    minmax( n, m, minl, maxl, minc, maxc );
    for i:= minl to maxl do
    begin
        for j:= minc to maxc do
        begin
            if mat[i, j] = num then
                achou:= achou + 1;
        end;
    end;
    if achou > 1 then
        tem:= true
    else
        tem:= false;
end;

function sud( var mat : matriz ) : boolean;
var i, j : integer; certo : boolean;

begin
    certo:= true;
    for i:= 1 to LIN do
    begin
        for j:= 1 to COL do
            if tem( mat, mat[i, j], i, j ) then
                certo:= false;
    end;
    sud:= certo;
end;

begin
    leMat( mat );
    if sud( mat ) then
        writeln( 'SIM' )
    else
        writeln( 'NAO' );
end.
