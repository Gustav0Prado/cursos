program ocorrencias;
const
    MIN = 1;
    MAX = 100;
type
    vet = Array[MIN..MAX] of integer;     //vet com os nums
var
    n    : vet;     //inicializa variaveis função principal
    m    : vet;
    tamn : integer;
    tamm : integer;
    quant : integer;

procedure leN( var n : vet; tamn : integer );     //le vetor dos nums n
var cont : integer;

begin
    for cont:= 1 to tamn do
        read( n[cont] );
end;

procedure leM( var m : vet; tamm : integer );   //le vetor dos nums m
var cont : integer;

begin
    for cont:= 1 to tamm do
        read( m[cont] );
end;

function ehSub( i : integer; var m : vet; tamsub : integer ) : boolean;  //func retorna se eh subseq ou nao
var ind, ini : integer; sub : boolean;

begin
    ind:= 1;    //começa com o primeiro elem de m
    sub:= true; //inicializa com true
    for ini:= i to i + tamsub - 1 do
    begin
        if n[ini] <> m[ind] then
            sub:= false;    //falso se seq não continua
        ind:= ind + 1;      //prox num da sequencia
    end;
    ehSub:= sub;        //retorna boolean
end;

function AchaOcorr( var n : vet; tamn : integer; var m : vet; tamm : integer ) : integer;         //função retorna quantas vezes uma subseq aparece
var tamsub, ini, cont : integer;

begin
    cont:= 0;           //inicializa cont
    tamsub:= tamm;      //tamanho da subseq = tam da seq a achar
    for ini:= 1 to tamn - tamsub + 1 do     //loop de ini
    begin
        if ehSub( ini, m, tamsub ) then     //função verifica se seq eh igual a seq m
            cont:= cont + 1;                //conta quantas vezes a subseq aparece
    end;
    AchaOcorr:= cont;   //retorno da função
end;

begin
    read( tamn );       //tamanho do vetor com os numeros
    read( tamm );       //tamanho do vetor com a sequencia
    leN( n, tamn );     //le vetor com os numeros
    leM( m, tamm );     //le vetor com a sequencia
    quant:= AchaOcorr( n, tamn, m, tamm );     //retorno da funcao de ocorrencias
    writeln( quant );
end.
