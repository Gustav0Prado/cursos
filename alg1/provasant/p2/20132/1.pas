program limite_da_soma;
const
    MIN = 1;
    MAX = 100;
type
    vet = Array[MIN..MAX] of integer;
var
    v      : vet;
    w      : vet;
    tamv   : integer;
    tamw   : integer;
    somax  : integer;

procedure leVet( var v : vet; var tamv : integer );
var num : integer;

begin
    read( num );
    while num <> 0 do
    begin
        tamv:= tamv + 1;
        v[tamv]:= num;
        read( num );
    end;
end;

procedure somaVet( var v, w : vet; tamv, somax : integer; var tamw : integer );
var i, soma : integer;

begin
    soma:= 0;
    for i:= 1 to tamv do
    begin
        soma:= soma + v[i];
        if soma >= somax  then
        begin
            soma:= 0;
            tamw:= tamw + 1;
            w[tamw]:= v[i];
        end;
    end;
end;

procedure escreVet( var w : vet; tamw : integer );
var i : integer;

begin
    for i:= 1 to tamw do
        write( w[i], ' ' );
    writeln;
end;

begin
    tamv:= MIN - 1;
    tamw:= MIN - 1;
    leVet( v, tamv );
    read( somax );
    somaVet( v, w, tamv, somax, tamw );
    escreVet( w, tamw );
end.
