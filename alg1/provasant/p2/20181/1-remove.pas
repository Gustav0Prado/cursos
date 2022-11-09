program removedor_array;
const
    MIN = 1;
    MAX = 100;
type
    vet = array[MIN..MAX] of integer;
var
    v   : vet;
    tam : integer;
    num : integer;
    pos : integer;

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

procedure remove( var v : vet; var tam : integer; pos, num : integer );
var i : integer;

begin
    if pos + num < tam then
    begin
        for i:= pos to pos + num - 1 do
            v[i]:= v[i + num ];
        for i:= pos + num to tam do
            v[i]:= v[i + num];
        tam:= tam - num;
    end;
end;

begin
    tam:= MIN - 1;
    leVet( v, tam );
    for num:= 1 to tam do
        write( v[num], ' ' );
    writeln;
    writeln( 'escreva a posição e quantos elemntos remover: ' );
    read( pos, num );
    remove( v, tam, pos, num );
    for num:= 1 to tam do
        write( v[num], ' ' );
    writeln;
end.
