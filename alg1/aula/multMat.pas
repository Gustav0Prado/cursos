program multiplica_matrizes;
type
    matriz = array[1..4, 1..4] of integer;
var
    A  : matriz;
    B  : matriz;
    AB : matriz;
    lin_AB : integer;
    col_AB : integer;

procedure leMatrizes( var A : matriz; iA, jA : integer; var B : matriz; iB, jB : integer);
var i, j : integer;

begin
    for i:= 1 to iA do
    begin
        for j:= 1 to jA do
            read( A[i, j] );
    end;
    for i:= 1 to iB do
    begin
        for j:= 1 to jB do
            read( B[i, j] );
    end;
end;

procedure multMat( var A : matriz;  lA, cA : integer;
                   var B : matriz;  lB, cB : integer;
                   var AB: matriz;  var lAB, cAB : integer );
var i, j, k : integer;

begin
    lAB:=lA;
    cAB:= cB;
    for i:= 1 to lAB do
    begin
        for j:= 1 to cAB do
        begin
            AB[i, j]:= 0;
            for k:= 1 to lB do
                AB[i, j]:= AB[i, j] + A[i, k]  * B[k, j];
        end;
    end;
end;

procedure escMat( var mat : matriz; lAB, cAB : integer );
var i, j : integer;

begin
    for i:= 1 to lAB do
    begin
        for j:= 1 to cAB do
            write( mat[i, j], ' ' );
        writeln;
    end;
end;

begin
    leMatrizes( A, 4, 3, B, 3, 4 );
    writeln( 'A : ' );
    escMat( A, 4, 3 );
    writeln( 'B : ' );
    escMat( B, 3, 4 );
    multMat( A, 4, 3, B, 3, 4, AB, lin_AB, col_AB );
    writeln( 'AB : ' );
    escMat( AB, lin_AB, col_AB );
end.
