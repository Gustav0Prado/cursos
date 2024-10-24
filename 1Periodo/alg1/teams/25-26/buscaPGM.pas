program buscaPGM;
const
   MAX	  = 1000;
   PRETO  = 0;
type
   TpMatriz = array[1..MAX, 1..MAX] of integer;
var
   arqIm, arqP, arqSai		        : text;
   nomeArqIm, nomeArqP, nomeArqSai : string[30];
   im, imP			                 : TpMatriz;
   numLin, numCol, numMax	        : integer;
   linP, colP, maxP		           : integer;
   i, j				                 : integer;

procedure leArqPGM(var f : text;
		   var m : TpMatriz; var numLin, numCol, numMax: integer);
var
   id	: string;
   i, j	: integer;
begin
   readln( f, id );
   readln( f, numCol, numLin );
   readln( f, numMax );
   for i:=1 to numLin do
      for j:= 1 to numCol do
	 read( f, m[i,j] );
end; { leArqPGM }

procedure escreveArqPGM(var f : text;
		  var m	: TpMatriz; numLin, numCol, numMax:integer);
var
   i, j	: integer;
begin
   writeln( f, 'P2' );
   writeln( f, numCol:4, numLin:4 );
   writeln( f, numMax );
   for i:= 1 to numLin do
   begin
      for j:= 1 to numCol do
	 write(f, m[i,j]:4);
      writeln( f );
   end;
end; { escreveArqPGM }

(*  Funcao achouPadrao:
 *  retorna true se o padrao de imagem imP com tamanho linP s colP
 *  for encontrado na imagem im com o canto superior esquerdo na posicao
 *  (linIni, colIni) *)

function achouPadrao(var im  : TpMatriz; linIni, colIni: integer;
var imP : TpMatriz; linP, colP: integer) : boolean;
var i, j: integer; igual: boolean;

begin
   igual:= true;
   i:= 1;
   while ( i <= linP ) AND igual do       //while para se for im for diferente
   begin                                  
      for j:= 1 to colP do
      begin
         if imP[i, j] <> im[ linIni + i - 1, colIni + j - 1] then
            igual:= false; 
      end;
      i:= i + 1;
   end;
   achouPadrao:= igual;
end; { achouPadrao }


(* Procedimento bordaPreta:
 * altera a imagem im, colocando uma borda de cor PRETO de tamanho
 * numLin x numCol com o canto superior esquerdo na posicao (linIni, colIni) *)

procedure bordaPreta (var im : TpMatriz; 
      linIni, colIni, numLin, numCol: integer);
var i, j: integer;

begin
   for i:= linIni to linIni + numLin do   //borda na primeira e ultima linha
   begin
      im[i, colIni]:= PRETO;
      im[i, colIni + numCol]:= PRETO;
   end;
   for j:= colIni to colIni + numCol do
   begin
      im[linIni, j]:= PRETO;              //borda na primeira e ultima coluna
      im[linIni + numLin, j]:= PRETO;
   end;
end; { bordaPreta }

begin
   writeln('Arquivo imagem PGM: ');  
   readln( nomeArqIm );
   assign( arqIm, nomeArqIm );
   reset( arqIm );
   leArqPGM( arqIm, im, numLin, numCol, numMax );
   close( arqIm );
   
   writeln('Arquivo padrao PGM: ');
   readln( nomeArqP );
   assign( arqP, nomeArqP );
   reset( arqP );
   leArqPGM( arqP, imP, linP, colP, maxP );
   close( arqP );
   
   for i:=1 to numLin-linP+1 do
   begin 
      for j:=1 to numCol-colP+1 do
      begin
         if achouPadrao(im, i, j, imP, linP, colP) then
            bordaPreta(im, i, j, linP, colP);
      end;
   end;

   writeln('Arquivo saida PGM: ');
   readln( nomeArqSai );
   assign( arqSai, nomeArqSai );
   rewrite( arqSai );
   escreveArqPGM( arqSai, im, numLin, numCol, numMax );
   close( arqSai );
end.
