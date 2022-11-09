program divide_media;
const
    MIN = 1;
    MAX = 100;
type
    vet = array[MIN..MAX] of integer;
var
    v    : vet;
    ac   : vet;
    ab   : vet;
    tamc : integer;
    tamb : integer;
    tam  : integer;

procedure leVet( var v : vet; var tam : integer );
var num : integer;

begin
    read( num );
    while num <> 0 do
    begin
        tam:= tam + 1;
        v[tam]:= num;
        read( num );
    end;
end;

function mediaVetor( var v : vet; tam : integer ) : real;
var i, soma : integer;

begin
    soma:= 0;
    for i:= MIN to tam do
        soma:= soma + v[i];
    mediaVetor:= soma/tam;
end;

procedure divide( var v, ab, ac : vet; tam : integer; var tamb, tamc : integer );
var i : integer; media : real;

begin
    media:= mediaVetor( v, tam );
    for i:= MIN to tam do
    begin
        if v[i] >= media then
        begin
            tamc:= tamc + 1;
            ac[tamc]:= v[i];
        end
        else
        begin
            tamb:= tamb + 1;
            ab[tamb]:= v[i];
        end;

    end;
end;

procedure escreve( var ac, ab : vet; tamc, tamb : integer );
var i : integer;

begin
    for i:= MIN to tamb do
        write( ab[i], ' ' );
    writeln;
    for i:= MIN to tamc do
        write( ac[i], ' ' );
    writeln;
end;

begin
    tam:= MIN - 1;
    tamb:= MIN - 1;
    tamc:= MIN - 1;
    leVet( v, tam );
    divide( v, ab, ac, tam, tamb, tamc );
    escreve( ac, ab, tamc, tamb );
end.
