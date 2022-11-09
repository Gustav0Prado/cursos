program bota;
const
    MIN = 1;
    MAX = 100;
type
    vet = array[MIN..MAX] of integer;
var
    m    : vet;
    n    : vet;
    k    : integer;
    tamn : integer;
    tamm : integer;

procedure leVets( var m, n : vet; tamm, tamn : integer );
var i : integer;

begin
    for i:= 1 to tamm do
        read( m[i] );
    for i:= 1 to tamn do
        read( n[i] );
end;

procedure insere( k : integer; var m, n : vet; var tamm, tamn : integer );
var i, ind : integer;

begin
    tamm:= tamm + tamn;
    ind:= MIN;
    for i:= tamm downto k do
        m[i]:= m[i - tamn];
    for i:= k to k + tamn - 1 do
    begin
        m[i]:= n[ind];
        ind:= ind + 1;
    end;
end;

procedure escreve( var m : vet; tamm : integer );
var i : integer;

begin
    for i:= MIN to tamm do
        write( m[i], ' ' );
    writeln;
end;

begin
    read( tamm, tamn );
    leVets( m, n, tamm, tamn );
    read( k );
    insere( k, m, n, tamm, tamn );
    escreve( m, tamm );
end.
