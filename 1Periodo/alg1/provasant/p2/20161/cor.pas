program cores_sla;
const
    MIN = 1;
    MAX = 100;
type
    vet = array[MIN..MAX] of integer;
var
    s   : vet;
    v   : vet;
    tam : integer;
    vets: integer;
    err : integer;
    cer : integer;
    val : boolean;
    iguais : boolean;

procedure leS( var s : vet; tam : integer );
var i : integer;

begin
    for i:= 1 to tam do
        read( s[i] );
end;

function jatem( num : integer; var v : vet; tam : integer ) : boolean;
var i : integer; achou : boolean;

begin
    achou:= false;
    for i:= MIN to tam do
    begin
        if v[i] = num then
            achou:= true;
    end;
    jatem:= achou;
end;

procedure leV( var v : vet; var tam : integer; var val : boolean);
var i, num : integer;

begin
    for i:= MIN to tam do
        v[i]:= 0;
    val:= true;
    for i:= MIN to tam do
    begin
        read( num );
        if jatem( num, v, tam ) then
            val:= false;
        v[i]:= num;
    end;
end;

function igual( var s, v : vet; tam : integer; var err, cer : integer ) : boolean;
var i : integer; ig : boolean;

begin
    cer:= 0;
    err:= 0;
    ig:= true;
    for i:= 1 to tam do
    begin
        if ( v[i] <> s[i] ) AND jatem( v[i], s, tam ) then
        begin
            err:= err + 1;
            ig:= false;
        end
        else if v[i] <> s[i]  then
            ig:= false
        else
            cer:= cer + 1;
    end;
    igual:= ig;
end;

begin
    vets:= 0;
    write( 'n      : ' );
    read( tam );
    write( 'Entrada: ' );
    leS( s, tam );
    write( 'Entrada: ' );
    leV( v, tam, val );
    iguais:= igual( s, v, tam, err, cer );
    while not iguais do
    begin
        vets:= vets + 1;
        if not val then
            writeln( 'Saida  : entrada invalida.' )

        else
            writeln( 'Saida  : cores no lugar certo: ', cer, ', cores no lugar errado: ', err, '.' );
        write( 'Entrada: ' );
        leV( v, tam, val );
        iguais:= igual( s, v, tam, err, cer );
    end;
    writeln( 'Foram lidos ', vets, ' vetores' );
end.
