Program labirinto_memes;
uses crt;

Const
   MAX = 100;
   PAREDE = -1;
   VAZIO = 0;
   LIN = 1;
   COL = 2;
Type
   labirinto= array [1..MAX,1..MAX] of integer;
   coordenada = array [1..2] of integer;
   fila= array [1..MAX] of coordenada;
Var
   L: labirinto;
   tamL, entrada, saida, elem, vizinho: coordenada;
   F: fila; tamF: integer;
   distancia: integer;
   i, j: integer;

procedure iniciaFila( var F: fila; var tamF: integer );
begin
   tamF:= 0;
end;

procedure lerLabirinto( var L: labirinto; var tamL, entrada, saida: coordenada );
var i, j: integer;

begin
   for i:= 1 to 2 do
      read( tamL[i] );
   for i:= 1 to 2 do
      read( entrada[i] );
   for i:= 1 to 2 do
      read( saida[i] );
   for i:= 1 to tamL[1] do
   begin
      for j:= 1 to tamL[2] do
         read( L[i, j] );
   end;
end;

procedure marcaElemLabirinto (var L: labirinto; elem: coordenada; distancia: integer);
begin
   L[elem[1], elem[2]]:= distancia;
end;

procedure insereElemFila( var F: fila; var tamf: integer; elem: coordenada );
begin
   tamf:= tamf + 1;
   F[tamF, 1]:= elem[1];
   F[tamF, 2]:= elem[2];
end;

procedure retiraElemFila( var F: fila; var tamF: integer; var elem: coordenada );
var i: integer;

begin
   elem[1]:= F[1, 1];
   elem[2]:= F[1, 2];
   for i:= 1 to tamF - 1 do
   begin
      F[i, 1]:= F[i + 1, 1];
   end;
   for i:= 1 to tamF - 1 do
   begin
      F[i, 2]:= F[i + 1, 2];
   end;
   tamf:= tamf - 1;
end;

function valorElemLabirinto( var L: labirinto; elem: coordenada ):integer;
begin
   valorElemLabirinto:= L[ elem[1], elem[2] ];
end;

function filaVazia( var F: fila; tamf: integer ): boolean;
begin
   if tamf = 0 then
      filaVazia:= true;
end;

function achavizinho( var L: labirinto; var tamL, elem, vizinho: coordenada ): boolean;
var cima, baixo, esq, dir: integer;

begin
   if elem[1] = tamL[1] then
      baixo:= -1
   else
      baixo:= L[elem[1] + 1, elem[2]];
   if elem[1] = 1 then
      cima:= -1
   else
      cima:= L[elem[1] - 1, elem[2] ];
   if elem[2] = 1 then
      esq:= -1
   else
      esq:= L[elem[1], elem[2] - 1];
   if elem[2] = tamL[2] then
      dir:= -1
   else
      dir:= L[elem[1], elem[2] + 1];
   if dir = 0 then
   begin
      vizinho[1]:= elem[1];
      vizinho[2]:= elem[2] + 1;
   end
   else if esq = 0 then
   begin
      vizinho[1]:= elem[1];
      vizinho[2]:= elem[2] - 1;
   end
   else if cima = 0 then
   begin
      vizinho[1]:= elem[1] - 1;
      vizinho[2]:= elem[2];
   end
   else if baixo = 0 then
   begin
      vizinho[1]:= elem[1] + 1;
      vizinho[2]:= elem[2];
   end;
   if ( cima = 0 ) OR ( baixo = 0 ) OR ( esq = 0 ) OR ( dir = 0 ) then
      achavizinho:= true
   else
      achavizinho:= false;
end;

function achavizinhoMenor( var L: labirinto; var tamL, elem, vizinho: coordenada; var num: integer ): boolean;
var cima, baixo, esq, dir: integer;

begin
   if elem[1] = tamL[1] then
      baixo:= MAX
   else
      baixo:= L[elem[1] + 1, elem[2]];
   if elem[1] = 1 then
      cima:= MAX
   else
      cima:= L[elem[1] - 1, elem[2] ];
   if elem[2] = 1 then
      esq:= MAX
   else
      esq:= L[elem[1], elem[2] - 1];
   if elem[2] = tamL[2] then
      dir:= MAX
   else
      dir:= L[elem[1], elem[2] + 1];
   if dir = num then
   begin
      vizinho[1]:= elem[1];
      vizinho[2]:= elem[2] + 1;
   end
   else if esq = num then
   begin
      vizinho[1]:= elem[1];
      vizinho[2]:= elem[2] - 1;
   end
   else if cima = num then
   begin
      vizinho[1]:= elem[1] - 1;
      vizinho[2]:= elem[2];
   end
   else if baixo = num then
   begin
      vizinho[1]:= elem[1] + 1;
      vizinho[2]:= elem[2];
   end;
   if ( cima = num ) OR ( baixo = num ) OR ( esq = num ) OR ( dir = num ) then
      achavizinhoMenor:= true
   else
      achavizinhoMenor:= false; 
end;

procedure imprimeMenorCaminho(var L: labirinto; entrada: coordenada);
var num, i, j, maxim: integer;
begin
   iniciaFila( F, tamF );
   insereElemFila( F, tamF, entrada );
   num:= L[entrada[1], entrada[2]] - 1;
   maxim:= num + (100 - num);
   repeat
      retiraElemFila( F, tamF, elem );
      if achavizinhoMenor( L, tamL, elem, vizinho, num ) then
         insereElemFila( F, tamF, vizinho );
      if num > 1 then
         num:= num - 1;
      L[elem[1], elem[2]]:= maxim;
   until ( filaVazia(F, tamF) );
   writeln( 'Menor Caminho: ' );
   for i:= 1 to tamL[1] do
   begin
      for j:= 1 to tamL[2] do
      begin
         if L[i, j] = 100 then 
         begin
            textColor( Blue );
            write( 'x':3, ' ' );
         end
         else
         begin
            textColor( white );
            write( L[i, j]:3, ' ' );
         end;
      end;
      writeln;
   end;
end;

Begin
   iniciaFila(F, tamF);
   distancia := 1;
   lerLabirinto(L, tamL, entrada, saida);
   marcaElemLabirinto(L, saida, distancia);
   insereElemFila (F, tamF, saida);
   writeln;
   repeat
      retiraElemFila(F, tamF, elem);
      distancia:= valorElemLabirinto(L, elem) + 1;
      while achavizinho( L, tamL, elem, vizinho ) do
      begin
         marcaElemLabirinto(L, vizinho, distancia);
         insereElemFila(F, tamF, vizinho);
      end;
   until (filaVazia(F, tamF));
   writeln;
   for i:= 1 to tamL[1] do
   begin
      for j:= 1 to tamL[2] do
         write( L[i, j]:3, ' ' );
      writeln;
   end;
   writeln;
   imprimeMenorCaminho(L, entrada);
End.