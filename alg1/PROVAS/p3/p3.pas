program prova3;
type matriz = array[1..100, 1..100] of integer;

var 
    mat : matriz;
    n   : integer;
    m   : integer;
    d   : integer;

procedure criaMatriz( var mat: matriz; n, m: integer );   //cria matriz nxm
var i, j: integer;
begin
    for i:= 1 to n do
    begin
        for j:= 1 to m do
            mat[i, j]:= 0;              //inicia matriz com zeros
    end;
    read(i, j);                          //le posicao do num 1
    while ( i <> 0 ) OR ( j <> 0 ) do    //enquanto i e j <> de 0   
    begin
        mat[i, j]:= 1;                  //posicao recebe numero 1
        read( i, j );
    end;
end;

procedure escreveMatriz( var mat: matriz; n, m: integer );
var i, j: integer;
begin
    for i:= 1 to n do
    begin
        for j:= 1 to m do
            write( mat[i, j]:2, ' ' );
        writeln;
    end;    
end;

function achaIlha( var mat: matriz; n, m, l, c, d: integer ): integer;  //retorna numero de elementos '1' em uma submatriz
var achou, linIni, colIni, linFim, colFim, i, j: integer;
begin
    achou:= 0;
    if l - d < 1 then               //delimita limites dos elementos
        linIni:= 1
    else
        linIni:= l - d;
    if l + d > n then
        linFim:= n
    else
        linFim:= l + d;
    if c - d < 1 then
        colIni:= 1
    else
        colIni:= c - d;
    if c + d > m then
        colFim:= m
    else
        colFim:= c + d;
    for i:= linIni to linFim do         //procura nos limites da submatriz
    begin
        for j:= colIni to colFim do
        begin
            if mat[i, j] = 1 then
                achou:= achou + 1;
        end;
    achaIlha:= achou;
    end;

end;

function contaIlhas( var mat: matriz; n, m, d: integer): integer;   //conta numero de ilhas encontradas
var lin, col, cont: integer;
begin
    cont:= 0;
    for lin:= 1 to n do
    begin
        for col:= 1 to m do
        begin
            if mat[lin, col] = 1 then       //manda os elem 1 para achar ilha
            begin
                if achaIlha( mat, n, m, lin, col, d ) = 1 then //se achar apenas um elem um na submmatriz, eh uma ilha
                    cont:= cont + 1;
            end;
        end;
    end;
    contaIlhas:= cont;
end;

begin
    write( 'Entre com o número de linhas e colunas da matriz: ' );
    read( n, m );
    writeln( 'Entre com as posicoes da matriz com valor 1:' );
    criaMatriz( mat, n, m );
    writeln( 'Matriz de entrada:' );
    escreveMatriz( mat, n, m );
    write( 'Entre com a distancia minima entre as ilhas: ' );
    read( d );
    write( 'Ilhas com distancia ', d, ' = ' );
    write( contaIlhas( mat, n, m, d ) );
    writeln;
end.