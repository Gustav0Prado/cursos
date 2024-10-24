program transpor_matriz;
type
    matriz = Array[1..50, 1..50] of integer;
var
    matA : matriz;
    matB : matriz;
    matT : matriz;
    nA   : integer;
    mA   : integer;
    nB   : integer;
    mB   : integer;

procedure leMat( var mat : matriz; n, m : integer );
var i, j : integer;

begin
    for i:= 1 to m do
    begin
        for j:= 1 to n do
            read( mat[i, j] );
    end;
end;

procedure transp( var mat, matT : matriz; var n,m : integer );
var i, j : integer;

begin
    i:= n;
    n:= m;
    m:= i;
    for i:= 1 to m do
    begin
        for j:= 1 to n do
            matT[i, j]:= mat[j, i];
    end;
end;

function igual( var matA, matB : matriz; n, m : integer ) : boolean;
var i, j : integer; eh_igual : boolean;

begin
    eh_igual:= true;
    for i:= 1 to m do
    begin
        for j:= 1 to n do
        begin
            if matA[i, j] <> matB[i, j] then
                eh_igual:= false;
        end;
    end;
    igual:= eh_igual;
end;

begin
    read( nA, mA );
    writeln;
    leMat( matA, nA, mA );
    writeln;
    read( nB, mB );
    writeln;
    leMat( matB, nB, mB );
    transp( matA, matT, nA, mA );
    if igual( matT, matB, nA, mA ) then
        writeln( 'sim' )
    else
        writeln( 'nao' );
end.
