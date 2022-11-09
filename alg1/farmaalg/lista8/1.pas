program maxim_soma;
const
    MIN = 1;
    MAX = 100;
type
    vet = Array[MIN..MAX] of integer;
var
    v          : vet;
    tam        : integer;
    indIni     : integer;
    indFim     : integer;
    somaMaior  : integer;

procedure leVetor( var v : vet; tam : integer );
var cont : integer;

begin
    cont:= 1;
    while cont <= tam do
    begin
        read( v[cont] );
        cont:= cont + 1;
    end;
end;

function maiorSoma( var v : vet; tam : integer; var indIni : integer; var indFim : integer ) : integer;
var
    soma  : integer;
    maior : integer;
    i     : integer;
    ind   : integer;
    tamsub: integer;

begin
    maior:= v[1];
    for tamsub:= 1 to tam do
    begin
        for ind:= 1 to tam - tamsub + 1 do
        begin
            soma:= 0;
            for i:= ind to ind + tamsub - 1 do
            begin
                soma:= soma + v[i];
                if soma > maior then
                begin
                    maior:= soma;
                    indIni:= ind;
                    indFim:= i;
                end;
            end;
        end;
    end;
    maiorSoma:= maior;
end;



begin
    read( tam );
    leVetor( v, tam );
    somaMaior:= maiorSoma( v, tam, indIni, indFim );
    writeln( 'a maior soma eh ', somaMaior );
    if indIni <> indfim then
        writeln( 'v[', indIni, '] até ', 'v[', indFim, ']' )
    else
        writeln( 'apenas v[', indIni, ']' );
end.
