program ocorrencias;
const
    MIN = 1;
    MAX = 100;
type
    vet = array[MIN..MAX] of integer;
var
    v    : vet;
    n    : vet;
    i    : integer;
    tamv : integer;
    tamn : integer;

function tem( var v : vet; tamv : integer; num : integer; var pos : integer ) : boolean;
var i : integer; jatem : boolean;

begin
    pos:= 1;
    jatem:= false;
    for i:= MIN to tamv do
    begin
        if v[i] = num then
        begin
            pos:= i;
            jatem:= true;
        end
    end;
    tem:= jatem;
end;


procedure lecont( var v : vet; tamv : integer; var n : vet; var tamn : integer );
var num, pos : integer; jatem : boolean;

begin
    read( num );
    while num <> 0 do
    begin
        if tem( v, tamv, num, pos ) then
        begin
            n[pos]:= n[pos] + 1;
        end
        else
        begin
            tamv:= tamv + 1;
            v[tamv]:= num;
            tamn:= tamn + 1;
            n[tamn]:= n[tamn] + 1;
        end;
        read( num );
    end;
end;

procedure escreVet( var v : vet; var n : vet; tamn : integer );
var i : integer;

begin
    for i:= MIN to tamn do
        writeln( v[i], ' : ', n[i], ' vezes' );
end;

begin
    tamv:= MIN - 1;
    tamn:= MIN - 1;
    leCont( v, tamv, n, tamn );
    for i:= MIN to tamn do
        write( v[i], ' ' );
    writeln;
    escreVet( v, n, tamn );
end.
