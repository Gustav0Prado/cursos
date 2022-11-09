program par_maior_menor;
const
    MIN = 0;
    MAX = 200;
type
    vet = array[MIN..MAX] of integer;
var
    v   : vet;
    vPar: vet;
    tam : integer;
    cont: integer;
    num : integer;
    ind : integer;

procedure insereOrd( num : integer; var v : vet; var tam : integer );
var i : integer;

begin
    i:= tam;
    while ( i >= MIN ) and ( v[i] > num ) do        //até achar v[i] menor que num
    begin
        v[i + 1]:= v[i];        //shift para esquerda dos nums do vetor
        i:= i - 1;
    end;
    v[i + 1]:= num;
    tam:= tam + 1;
end;

function jatem( num1, num2 : integer; var vetor : vet; tam : integer ) : boolean;
var i, veti : integer; achou1, achou2, tem : boolean;

begin
    achou1:= false;     //variaveis para sinalizar o primeiro e e segundo
    achou2:= false;
    for i:= 1 to tam do
    begin
        veti:= vetor[i];        //calcula valor do vetor apenas uma vez
        if veti = num1 then
            achou1:= true
        else if veti = num2 then
            achou2:= true;
    end;
    if achou1 AND achou2 then       //caso tenha acahdo os dois
        tem:= true
    else
        tem:= false;
    jatem:= tem;
end;


procedure Pares( var v, vPar : vet; tam : integer );
var maior, menor, pos : integer;

begin
    menor:= MIN;              //indice inicial do menor
    pos:= MIN;                //posição a ser inserido em vPar
    maior:= tam;
    while menor <= maior do        //depois que maior e menor se encontrarem, para o loop (contempla os numeros no meio)
    begin
        if not ( jatem( v[menor], v[maior], vPar, tam ) ) then  //so coloca no vetor se nao estiver
        begin
            vPar[pos]:= v[menor];
            vPar[pos  + 1]:= v[maior];
            pos:= pos + 2;
        end;
        menor:= menor + 1;
        maior:= maior - 1;
    end;
end;


procedure escreVet( var vetor : vet; tam : integer );       //escreve um vetor
var i : integer;

begin
    for i:= MIN to tam do                    //elementos de MIN ate tam
        write( vetor[i], ' ' );
    writeln;
end;

begin
    write( 'Tamanho da sequencia: ');
    read( tam );
    write( 'Entre com a sequencia: ');
    ind:= tam - 1;                        //vetor começa em zero, então tamanho 10 vai de 0 a 9
    cont:= MIN - 1;                      //primeira posição a inserir
    while cont <= ind - 1 do            //do minimo até o tam maximo le os nums ( con 8 le a posicao 9 )
    begin
        read( num );
        insereOrd( num, v, cont );       //insere os numeros ordernados
    end;
    Pares( v, vPar, ind );              //cria vetor com os pares
    escreVet( vPar, ind );              //escreve um vetor
end.

