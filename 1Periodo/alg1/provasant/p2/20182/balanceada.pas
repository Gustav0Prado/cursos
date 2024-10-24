program balanceada_teste;
const
    MIN = 1;
    MAX = 100;
type
    vet   = Array[MIN..MAX] of integer;
var
    v   : vet;
    tam : integer;
    num : integer;
    i   : integer;

procedure leOrd( num : integer; var v : vet; var tam : integer );
var i : integer;

begin
    i:= tam;
    while ( i>= MIN ) AND (v[i] > num ) do
    begin
        v[i+1]:= v[i];
        i:= i - 1;
    end;
    v[i+1]:= num;
    tam:= tam + 1;
end;

function balanca( v : vet; tam : integer ) : boolean;
var
    i        : integer;
    ind      : integer;
    balan    : integer;
    maior    : integer;
    menor    : integer;
    eh_balan : boolean;

begin
    eh_balan:= true;
    i:= tam;
    ind:= 1;
    balan:= v[tam] + v[1];
    while i > ind do
    begin
        maior:= v[i];
        menor:= v[ind];
        if maior + menor <> balan then
            eh_balan:= false;
        i:= i - 1;
        ind:= ind + 1;
    end;
    if eh_balan then
        balanca:= true
    else
        balanca:= false;
end;

begin
    tam:= MIN - 1;
    read( num );
    while num <> 0 do
    begin
        leOrd( num, v, tam );
        read( num );
    end;
    if balanca( v, tam ) then
        writeln( 'Sim, eh balanceada' )
    else
        writeln( 'Nao eh balanceada' );
end.
