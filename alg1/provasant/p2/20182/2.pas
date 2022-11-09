program fim_fila;
const
    MIN = 1;
    MAX = 100;
type
    vet = Array[MIN..MAX] of integer;
var
    v    : vet;
    r    : vet;
    tamv : integer;
    tamr : integer;
    num  : integer;

function tem( num : integer; var v : vet; tamv : integer ) : boolean;
var i : integer; jatem : boolean;

begin
    jatem:= false;
    for i:= 1 to tamv do
    begin
        if num = v[i] then
            jatem:= true;
    end;
    tem:= jatem;
end;

procedure insereV( num : integer; var v : vet; var tamv : integer );
begin
    tamv:= tamv + 1;
    v[tamv]:= num;
end;


procedure insereR( num : integer; var r : vet; var tamr : integer );
var i : integer;

begin
    i:= tamr;
    while ( i >= MIN ) AND ( r[i] > num ) do
    begin
        r[i + 1]:= r[i];
        i:= i - 1;
    end;
    r[i + 1]:= num;
    tamr:= tamr + 1;
end;

procedure escreveVetor( var v : vet; tamv : integer; var r : vet; tamr : integer );
var i : integer;

begin
    for i:= 1 to tamv do
        write( v[i], ' ' );
    for i:= 1 to tamr do
        write( r[i], ' ' );
    writeln;
end;

begin
    tamv:= MIN -  1;
    tamr:= MIN - 1;
    read( num );
    while num <> 0 do
    begin
        if not tem( num, v, tamv ) then
            insereV( num, v, tamv )
        else
            insereR( num, r, tamr );
        read( num );
    end;
    escreveVetor( v, tamv, r, tamr );
end.
