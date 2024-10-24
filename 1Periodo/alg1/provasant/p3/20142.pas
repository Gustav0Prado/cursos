program ordena_matriz;
type matriz = array[1..50, 1..50] of integer;
var 
   matA : matriz;
   matB : matriz;
   matZ : matriz;
   n    : integer;

procedure leMat( var mat: matriz; d: integer );
var i, j: integer;

begin
   for i:= 1 to d do
   begin
      for j:= 1 to d do
         read( mat[i, j] );
   end;
end;

function achaMenor( var mat: matriz; n, m: integer; l, c: integer; var  menor, posl, posc: integer ): boolean;
var lin, col: integer;

begin
   menor:= mat[l, c];
   col:= c + 1;
   for lin:= l to n do
   begin
      while col <= m do
      begin
         if mat[lin, col] < menor then
         begin
            menor:= mat[lin, col];
            posl:= lin;
            posc:= col;
         end;
         col:= col + 1
      end;
      col:= 1;
   end;
   if menor = mat[l, c] then
      achaMenor:= false
   else 
      achaMenor:= true;
end;

procedure ordena( var mat: matriz; n, m: integer );
var l, c, i, j, aux, menor, posl, posc: integer;

begin
   for l:= 1 to n do
   begin
      for c:= 1 to m do
      begin
         if achaMenor( mat, n, m, l, c, menor, posl, posc ) then
         begin
            aux:= mat[l, c];
            mat[l, c]:= menor;
            mat[posl, posc]:= aux;
         end;
      end; 
   end;
   writeln;
   for i:= 1 to n do
   begin
      for j:= 1 to m do
         write( mat[i, j]:3, ' ' );
      writeln;
   end;
   writeln;
end;

procedure concMat( var matA, matB, matZ: matriz; n, m: integer );
var lZ, cZ, l, c: integer;

begin
   m:= m * 2;
   for lZ:= 1 to n do
   begin
      for cZ:= 1 to m do
      begin
         matZ[lZ, cZ]:= matA[lZ, cZ];
      end;
   end;
   l:= 1;
   for lZ:= 1 to n do
   begin
      c:= 0;
      for cZ:= n + 1 to m do
      begin
         c:= c + 1;
         matZ[lZ, cZ]:= matB[l, c];
      end;
      l:= l + 1;
   end;
end;

begin
   read( n );
   leMat( matA, n );
   leMat( matB, n );
   writeln;
   writeln( 'Matriz A ordenada: ' );
   ordena( matA, n, n );
   writeln( 'Matriz B ordenada: ' );
   ordena( matB, n, n );
   concMat( matA, matB, matZ, n, n );
   writeln( 'Matriz Z ordenada: ' );
   ordena( matZ, n, (n * 2 ) );
end.