program scan_cpf;
const
    MIN = 1;
    MAX = 100;
type
    vet = Array[MIN..MAX] of int64;
    num = Array[MIN..MAX] of integer;
    val = Array[MIN..MAX] of string;
var
    v      : vet;
    nums   : num;
    vali   : val;
    tam    : integer;
    ind    : integer;
    tamnum : integer;
    verif1 : integer;
    verif2 : integer;

procedure leNums( var v : vet; var tam : integer );
var num : int64;

begin
    tam:= MIN - 1;
    read( num );
    while num <> 0 do
    begin
        tam:= tam + 1;
        v[tam]:= num;
        read( num );
    end;
end;

function contTam( cpf : int64; var nums : num ) : integer;
var ult, tam : integer;

begin
    tam:= MIN - 1;
    while cpf > 0 do
    begin
        tam:= tam + 1;
        ult:= cpf mod 10;
        nums[tam]:= ult;
        cpf:= cpf div 10;
    end;
    contTam:= tam;
end;

function checks1( var nums : num; tam : integer ) : integer;
var mult, soma, resto : integer;

begin
    soma:= 0;
    mult:= 2;
    for tam:= 3 to 11 do
    begin
        soma:= soma + ( nums[tam] * mult );
        mult:= mult + 1;
    end;
    resto:= soma mod 11;
    if resto < 2 then
        checks1:= 0
    else
        checks1:= 11 - resto;
end;

function checks2( var nums : num; tam : integer ) : integer;
var mult, soma, resto : integer;

begin
    soma:= 0;
    mult:= 2;
    for tam:= 2 to 11 do
    begin
        soma:= soma + ( nums[tam] * mult );
        mult:= mult + 1;
    end;
    resto:= soma mod 11;
    if resto < 2 then
        checks2:= 0
    else
        checks2:= 11 - resto;
end;

begin
    leNums( v, tam );
    for ind:= 1 to tam do
    begin
        tamnum:= contTam( v[ind], nums );
        verif1:= checks1( nums, tamnum );
        verif2:= checks2( nums, tamnum );
        writeln( nums[1], ' ', verif2, ' ', nums[2], ' ', verif1 );
        if ( verif1 = nums[2] ) AND ( verif2 = nums[1] ) then
            vali[ind]:= 'valido'
        else
            vali[ind]:= 'invalido';
    end;
    for ind:= tam downto 1 do
    begin
        write( v[ind], ' ', vali[ind] );
        writeln;
    end;
    writeln;
end.
