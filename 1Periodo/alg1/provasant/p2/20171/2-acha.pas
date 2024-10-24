program acha_seq;
const
    MIN = 1;
    MAX = 100;
type
    vet = array[MIN..MAX] of integer;
var
    x    : vet;
    y    : vet;
    tamx : integer;
    tamy : integer;

procedure leVets( var x, y : vet; var tamx, tamy : integer );
var num : integer;

begin
    read( num );
    while num <> 0 do
    begin
        tamx:= tamx + 1;
        x[tamx]:= num;
        read( num );
    end;
    read( num );
    while num <> 0 do
    begin
        tamy:= tamy + 1;
        y[tamy]:= num;
        read( num );
    end;
end;

function quant( var x, y : vet; tamx, tamy : integer ) : integer;
var i, ind, indy, cont : integer; ehseq : boolean;

begin
    ind:= 1;
    cont:= 0;
    while ind <= tamy do
    begin
        i:= 1;
        if x[i] = y[ind] then
        begin
            indy:= ind;      //volta pro prox ind, nao pro fim da seq
            ehseq:= true;
            while ehseq AND ( indy <= tamy ) AND ( i <= tamx ) do
            begin
                if x[i] <> y[indy] then
                    ehseq:= false;
                i:= i + 1;
                indy:= indy + 1;
            end;
            if ehseq then
                cont:= cont + 1;
        end;
        ind:= ind + 1;     //volta pro prox ind, nao pro fim da seq
        quant:= cont;
    end;
end;

begin
    tamx:= MIN - 1;
    tamy:= MIN - 1;
    leVets( x, y, tamx, tamy );
    writeln( quant( x, y, tamx, tamy ) );
end.
