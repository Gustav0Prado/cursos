program batalha_naval;
Const
   MAX = 100;

type 
   matriz = array[1..200, 1..200] of integer;
   coordenada = array [1..2] of integer;
   fila= array [1..MAX] of coordenada;

var
   mat : matriz;
   jog : matriz;
   njog: integer;
   tamF: integer;
   F   : fila;
   vizinho: coordenada;
   elem: coordenada;
   tamM: coordenada;

procedure iniciaFila( var F: fila; var tamF: integer );
begin
   tamF:= 0;
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

function filaVazia( var F: fila; tamf: integer ): boolean;
begin
   if tamf = 0 then
      filaVazia:= true;
end;

function achavizinho( var L: matriz; var tamL, elem, vizinho: coordenada; var dest: boolean): boolean;
var cima, baixo, esq, dir: integer;

begin
   if elem[1] = tamL[1] then
      baixo:= 0
   else
      baixo:= L[elem[1] + 1, elem[2]];
   if elem[1] = 1 then
      cima:= 0
   else
      cima:= L[elem[1] - 1, elem[2] ];
   if elem[2] = 1 then
      esq:= 0
   else
      esq:= L[elem[1], elem[2] - 1];
   if elem[2] = tamL[2] then
      dir:= 0
   else
      dir:= L[elem[1], elem[2] + 1];
   if dir = 2 then
   begin
      vizinho[1]:= elem[1];
      vizinho[2]:= elem[2] + 1;
   end
   else if esq = 2 then
   begin
      vizinho[1]:= elem[1];
      vizinho[2]:= elem[2] - 1;
   end
   else if cima = 2 then
   begin
      vizinho[1]:= elem[1] - 1;
      vizinho[2]:= elem[2];
   end
   else if baixo = 2 then
   begin
      vizinho[1]:= elem[1] + 1;
      vizinho[2]:= elem[2];
   end;
   if ( cima = 2 ) OR ( baixo = 2 ) OR ( esq = 2 ) OR ( dir = 2 ) then
      achavizinho:= true
   else
      achavizinho:= false;
   if ( cima = 1 ) OR ( baixo = 1 ) OR ( esq = 1 ) OR ( dir = 1 ) then
      dest:= false;
end;

procedure leMat(var mat: matriz; tamM: coordenada);
var i, j: integer;
   input, espaco: char;

begin
   for i:= 1 to tamM[1] do
   begin
      for j:= 1 to tamM[2] do
      begin
         read( input );
         if input = '.' then
            mat[i, j]:= 0
         else
            mat[i, j]:= 1;
      end;
      read( espaco );
   end;   
end;

procedure jogadas( var mat, jog: matriz; lin, col: integer  );
var i, j1, j2: integer;

begin
    for i:= 1 to lin do
    begin
        read( j1, j2 );
        if mat[j1, j2] <> 0 then
            mat[j1, j2]:= 2;
    end;
end;

procedure escMat( var mat: matriz; l, c: integer );
var i, j: integer;

begin
    for i:= 1 to l do
    begin
        for j:= 1 to c do
            write( mat[i, j]:2, ' ' );
        writeln;
    end;
end;

procedure mudaElem( var mat: matriz; var elem: coordenada );
begin
   mat[elem[1], elem[2]]:= -1;
end;

procedure destruidos( var mat: matriz; tamM: coordenada; var F: fila; var tamF: integer );  //funciona até entrada 2
var l, c, cont: integer; coord: coordenada; dest: boolean;

begin
   cont:= 0;
   for l:= 1 to tamM[1] do
   begin
      for c:= 1 to tamM[2] do
      begin
         if mat[l, c] = 2 then
         begin
            dest:= true;
            iniciaFila( F, tamf );
            coord[1]:= l;
            coord[2]:= c;
            insereElemFila( F, tamF, coord );
            mat[coord[1], coord[2]]:= -1;
            repeat
               retiraElemFila( F, tamF, elem );
               while achavizinho( mat, tamM, elem, vizinho, dest ) do
               begin
                  insereElemFila( F, tamF, vizinho );
                  mudaElem( mat, vizinho );
               end;
            until ( filaVazia( F, tamF) );
            if dest then
               cont:= cont + 1;
         end;
      end;
   end;
   writeln( cont );
end;

begin
   readln( tamM[1], tamM[2] );
   leMat( mat, tamM );
   read( njog );
   jogadas( mat, jog, njog, 2 );
   escMat( mat, tamM[1], tamM[2] );
   destruidos( mat, tamM, F, tamF );
end.