program compactacaoo;
const
    MIN = 1;
    MAX = 100;
type
    vet = Array[MIN..MAX] of integer;
    com = Array[MIN..MAX] of integer;
var
    v    : vet;
    c    : com;
    tam  : integer;
    ind  : integer;
    tamc : integer;

function tem( num : integer; var c : com; tamc : integer ) : boolean;
var ind, cont : integer;

begin
    tem:= false;
    cont:= 0;
    for ind:= 1 to tamc do
    begin
        if c[ind] = num then
            cont:= cont + 1;
    end;
    if cont > 0 then
        tem:= true;
end;

procedure compVet( var v : vet; tam : integer; var c : com; var tamc : integer );
var i : integer; achou : boolean;

begin
    tamc:= MIN - 1;
    for i:= 1 to tam do
    begin
        if not tem( v[i], c, tamc ) then
        begin
            tamc:= tamc + 1;
            c[tamc]:= v[i];
        end;
    end;
end;

procedure leVet( var v : vet; tam : integer );
var i : integer;

begin
    for i:= 1 to tam do
        read( v[i] );
end;

begin
    read( tam );
    while tam <> 0 do
    begin
        leVet( v, tam );
        compVet( v, tam, c, tamc );
        write( 'O: ' );
        for ind:= 1 to tam do
            write( v[ind], ' ' );
        writeln;
        write( 'C: ' );
        for ind:= 1 to tamc do
            write( c[ind], ' ' );
        writeln;
        read( tam );
    end;
end.
