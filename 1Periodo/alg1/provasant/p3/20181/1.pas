program meu_pai_amado;
type matriz = array[1..50, 1..50] of integer;

var
   mat   : matriz;
   n     : integer;

procedure ler_matriz( var mat: matriz; n: integer );
var i, j: integer;

begin
   for i := 1 to n do
   begin
      for j := 1 to n do
         read( mat[i, j] );
   end;
end;

function achar_X( var mat: matriz; n, i, j, tam: integer ):boolean;
var lin, col, X: integer; 
   ehx: boolean;

begin
   ehx:= true;
   X:= mat[i, j];
   lin:= 0;
   col:= 0;
   while ( lin <= tam - 1 ) AND ( col <= tam - 1 ) AND ehx do
   begin
      if mat[i + lin, j + col] <> X then
         ehx:= false;
      lin:= lin + 1;
      col:= col + 1;
   end;
   lin:= 0;
   col:= tam - 1;
   while ( lin >= i + tam - 1 ) AND ( col >= j ) AND ehx do
   begin
      if mat[i + lin, j + col] <> X then
         ehx:= false;
      lin:= lin - 1;
      col:= col - 1;
   end;
   achar_X:= ehx;
end;

procedure inverte_cor( var mat: matriz; n: integer );
var i, j, maior: integer;

begin
   maior:= 0;
   for i:= 1 to n do
   begin
      for j := 1 to n do
      begin
         if mat[i, j] > maior then
            maior:= mat[i, j];
      end;
   end;
   for i:= 1 to n do
   begin
      for j := 1 to n do
         mat[i, j]:= maior - mat[i, j];
   end;
end;

procedure imprimir_matriz( var mat: matriz; n: integer );
var i, j: integer;

begin
   for i:= 1 to n do
   begin
      for j := 1 to n do
         write( mat[i, j]:2, ' ' );
      writeln;
   end;
end;

procedure achax( var mat: matriz; n: integer );
var i, j, tam, tammax: integer;
   achou: boolean;

begin
   achou:= false;
   i:= 1;
   while ( i <= n - 1 ) AND not achou do
   begin
      j:= 1;
      while ( j <= n - 1 ) AND not achou do
      begin
         if i > j then
            tammax:= n - i + 1
         else
            tammax:= n - j + 1;
         tam:= 2;
         while ( tam <= tammax ) AND not achou do
         begin 
            if achar_X( mat, n, i, j, tam ) then
            begin
               achou:= true;
               inverte_cor( mat, n );
            end;
            tam:= tam + 1;
         end;
         j:= j + 1;
      end;
      i:= i + 1;
   end;
end;

begin
   read( n );
   ler_matriz( mat, n );
   achax( mat, n );
   imprimir_matriz( mat, n );
end.