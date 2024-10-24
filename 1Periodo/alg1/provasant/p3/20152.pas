program matriz_pra_vetor;
type 
   matriz = array[1..50, 1..50] of integer;
   vetor = array[1..50] of integer;
var 
   mat : matriz;
   vet : vetor;
   d   : integer;
   tam : integer;


procedure leMat( var amt: matriz; n: integer );
var l, c: integer;

begin
   for l:= 1 to n do
   begin
      for c:= 1 to n do
         read( mat[l, c] );
   end;
end;

procedure numIguais( var mat: matriz; n: integer; var vet: vetor; var k: integer );
var i, j, matij: integer;

begin
   k:= 0;
   for i:= 1 to n do
   begin
      for j:= 1 to n do
      begin
         matij:= mat[i, j];
         if mat[j, i] = matij then
         begin
            k:= k + 1;
            vet[ k ]:= matij;
            mat[j, i]:= -1;   //tira o numero corresp para nao detectar duas vezes
         end;
      end;
   end;
end;

procedure remove( var vet: vetor; tam, ind: integer );
var k: integer;

begin
   for k:= ind + 1 to tam do
   begin
      vet[k - 1]:= vet[k];
   end;
end;

procedure ordena( var vet: vetor; tam: integer);
var i, menor, ind, j: integer;

begin
   while tam > 0 do
   begin
      menor:= vet[1];
      for i:= 1 to tam do
      begin
         if ( vet[i] < menor ) AND ( vet[i] <> -1 ) then
         begin
            menor:= vet[i];
            ind:= i;
         end;
      end;
      write( menor, ' ' );
      remove( vet, tam, ind );
      tam:= tam - 1;
   end;
   writeln;
end;

begin
   read( d );
   leMat( mat, d );
   writeln( 'ok' );
   numIguais( mat, d, vet, tam );
   ordena( vet, tam );
end.