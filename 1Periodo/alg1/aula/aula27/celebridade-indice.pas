(* Programa que determina se existe uma celebridade em uma festa 
   Uma pessoa P e' identificada como uma celebridade em uma festa se:
   Condicao 1: todos conhecem P
   Condicao 2: nao conhece ninguem

  Entrada do programa: 
    numero de pessoas
    conjunto de pares p1 p2 que representam o fato de p1 conhecer p2

 Solucao: conjunto
*)
program celebridade;

const max = 101;

type 
   tpmatriz   =  array [1..max, 1..max] of boolean;
   

var
   conhece    : tpMatriz;
   numPessoas, celeb : integer;


procedure leConhece(var conhece	: tpMatriz; numPessoas: integer );
var
   p1, p2 : integer;
begin
   for p1:= 1 to numPessoas do
      for p2:=1 to numPessoas do
	 conhece[p1,p2]:= false;
   readln( p1, p2 );
   while (p1<>0) and (p2<>0) do
   begin
      conhece[p1,p2]:= true;
      readln( p1, p2 );
   end;
end;

function todosConhecem(p : integer; conhece: tpMatriz; numPessoas: integer): boolean;
var
   i : integer;
begin
   todosConhecem:= true;
   for i:=1 to numPessoas do
      if not conhece[i,p] and (i<>p) then
	 todosConhecem:= false;
end;

function conheceNinguem(p : integer; conhece: tpMatriz; numPessoas: integer): boolean;
var
   i : integer;
begin
   conheceNinguem:= true;
   for i:=1 to numPessoas do
      if conhece[p,i] then
	 conheceNinguem:= false;
end;


function identificaCelebridade(var conhece : tpMatriz; numPessoas: integer ): integer;
var
   p1, p2  : longint;
begin
   p1:= 1;
   p2:= numPessoas;
   while p1 <> p2 do
      if conhece[p1, p2] then
	      p1:= p1+1
      else
	      p2:= p2-1;
   if todosConhecem( p1, conhece, numPessoas) and conheceNinguem( p1, conhece, numPessoas) then
      identificaCelebridade:= p1
   else
      identificaCelebridade:= 0;
end;

begin
   write( 'Entre com o numero de pessoas: ' );
   readln( numPessoas );
   writeln( 'Entre com pares de inteiros de quem conhece quem: ');
   leConhece( conhece, numPessoas );
   celeb:= identificaCelebridade( conhece, numPessoas );
   if celeb <> 0 then
      writeln( 'celebridade: ', celeb )
   else
      writeln( 'nao tem celebridade');
end.   

