program achador_de_borda;
type matriz = array[1..200, 1..200] of integer;

var
   mat    : matriz;
   n      : integer;
   num    : integer;
   tam    : integer;
   achouB : boolean;

procedure leMat(var mat: matriz; n: integer);
var l, c: integer;

begin
   for l := 1 to n do
   begin
      for c := 1 to n do
         read( mat[l, c] );
   end;
end;

function borda( var mat: matriz; n, tam, lin, col: integer; var num: integer ): boolean;
var i, j, prim: integer;
   ehborda: boolean;

begin
   prim:= mat[lin, col];
   ehborda:= true;
   i:= lin;
   while ( i <= lin + tam - 1 ) AND ehborda do
   begin
      if ( mat[i, 1] <> prim ) AND ( mat[i, tam] <> prim ) then
         ehborda:= false;
      i:= i + 1;
   end;
   j:= col;
   while ( j <= col + tam - 1 ) AND ehborda do
   begin
      if ( mat[1, j] <> prim ) AND ( mat[1, tam] <> prim ) then
         ehborda:= false;
      j:= j + 1;
   end;
   num:= prim;
   borda:= ehborda;
end;

function borda33( var mat: matriz; n: integer; var num: integer ): boolean;
var i, j, numer: integer;
   ehborda: boolean;

begin
   i:= 1;
   ehborda:= false;
   while ( i <= n - 3) AND not ehborda do
   begin
      j:= 1;
      while ( j <= n - 3 ) AND not ehborda do
      begin
         if borda( mat, n, 3, i, j, numer ) then
         begin
            ehborda:= true;
            numer:= mat[i + 1, j + 1];
         end;
         j:= j + 1;
      end;
      i:= i + 1;
   end;
   num:= numer;
   borda33:= ehborda;
end;

procedure removeNum( var mat: matriz; n, num: integer );
var i, j: integer;

begin
   for i := 1 to n do
   begin
      for j := 1 to n do
      begin
         if mat[i, j] = num then
            mat[i, j]:= 0;
      end;
   end;
end;

procedure escMat( var mat: matriz; n: integer);
var l, c: integer;

begin
   for l:= 1 to n do
   begin
      for c:= 1 to n do
         write( mat[l, c]:2, ' ' );
      writeln;
   end;
end;

begin
   read( n );
   leMat( mat, n );
   achouB:= false;
   tam:= 2;
   while ( tam <= n ) AND not achouB do
   begin
      if borda( mat, n, tam, 1, 1, num ) then
      begin
         achouB:= true;
         removeNum( mat, n, num );
      end;
      tam:= tam + 1;
   end;
   if borda33( mat, n, num ) then
   begin
      removeNum( mat, n, num );
      writeln( 'borda33' );
   end;
   escMat( mat, n );
end.