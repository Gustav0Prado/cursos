program escolha_um_nome_bom;

const MAX = 100;

type vetor = array [1..MAX] of longint;

var
    v : vetor;
    n, pos, tamanho_subsequencia: longint;

procedure ler_vetor (var v: vetor; n: longint);
var i : integer;

begin
    for i:= 1 to n do
        read( v[i] );
end;

function tem_subsequencia_iguais (var v: vetor; n : integer; tam_seg: longint): longint;
(*
recebe uma subsequencia "v" que tem tamanho "n" e procura por subsequencias
iguais de tamanho "tam_seg". A funcao devolve zero se nao encontrou
subsequencias iguais ou devolve a posicao do inicio da primeira subsequencia
que encontrou.
*)
var ini, ind, tams, indIni, fim, i : integer; ehsub : boolean;

begin
    tams:= n - tam_seg + 1;
    for ini:= 1 to tams  do
    begin
        for ind:= ini to tams do
        begin
            for fim:= ind + 1 to tams do
            begin
                ehsub:= true;
                i:= 1;
                if v[ind] = v[fim] then
                begin
                    while ( i < tam_seg ) AND ehsub do
                    begin
                        if v[ind + i] <> v[fim + i] then
                            ehsub:= false;
                        i:= i + 1;
                    end;
                    if ehsub then
                        indIni:= ini;
                end;
            end;
        end;
    end;
    tem_subsequencia_iguais:= indIni;
end;


(* programa principal *)
begin
    read (n);
    // tamanho da subsequencia a ser lido
    ler_vetor (v,n);
    pos:= 0;
    tamanho_subsequencia:= n div 2; // inicia com maior valor possivel
    while (pos = 0) and (tamanho_subsequencia >= 2) do
    begin
         pos:= tem_subsequencia_iguais (v,n,tamanho_subsequencia);
         tamanho_subsequencia:= tamanho_subsequencia - 1;
    end;
    if pos > 0 then
        writeln (pos,' ',tamanho_subsequencia+1 )
    else
        writeln ('nenhuma');
end.
