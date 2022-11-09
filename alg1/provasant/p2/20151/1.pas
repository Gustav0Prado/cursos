program sorteio_maluco;
const
    MIN = 1;
    MAX = 100;
type
    vet = array[MIN..MAX] of integer;
var
    v    : vet;
    tam : int64;
    num : integer;

function sorteia( var v : vet; tam, num : integer ) : integer;
var i : integer;

begin
    i:= Random(tam) - num;
    while i > tam do
        i:= i + num;
    while i < MIN do
        i:= i - num;
    sorteia:= v[i];
end;

begin
    Randomize;
    tam:= MIN - 1;
    read( num );
    while num <> 0 do
    begin
        if num < 0 then
            write( sorteia(v, tam, num), ' ' )
        else
        begin
            tam:= tam + 1;
            v[tam]:= num;
        end;
        read( num );
    end;
    writeln;
end.
