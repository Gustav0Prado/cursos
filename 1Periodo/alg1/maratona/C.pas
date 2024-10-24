program B;
type
   matriz = array[1..1000, 1..1000] of integer;
var
   mat : matriz;
   n, m, t, k: integer;

procedure leMat(var mat: matriz; n, m: integer);
var i, j: integer;
begin
   for i:= 1 to n do
   begin
      for j:= 1 to m do
         read(mat[i, j]);
   end;
end;

function queima(var mat: matriz; i, j, n, m: integer):boolean;
label 1, 2, 3, 4;
var matij, k, c3, c4: integer; var hand: array[0..7] of integer;
   vaiqueimar: boolean;
begin
   vaiqueimar:= false;
   matij:= mat[i, j];
   if i > 1 then
      hand[0]:= mat[i - 1, j]
   else
      hand[0]:= -1;
   if i < n then
      hand[1]:= mat[i + 1, j]
   else
      hand[1]:= -1;
   if j > 1 then
      hand[2]:= mat[i, j - 1]
   else
      hand[2]:= -1;
   if j < m then
      hand[3]:= mat[i, j + 1]
   else
      hand[3]:= -1;
   if (i > 1) AND (j > 1) then
      hand[4]:= mat[i - 1, j - 1]
   else
      hand[4]:= -1;
   if (i > 1) AND (j < m) then
      hand[5]:= mat[i - 1, j + 1]
   else
      hand[5]:= -1;
   if (i < n) AND (j > 1) then
      hand[6]:= mat[i - 1, j]
   else
      hand[6]:= -1;
   if (i < n) AND (j < m) then
      hand[7]:= mat[i - 1, j]
   else
      hand[7]:= -1;
   c3:= 0;
   c4:= 0;
   case (matij) of
      1: goto 1;
      2: goto 2;
      3: goto 3;
      4: goto 4;
   end;
   1: for k:= 0 to 7 do
      if hand[k] = 0 then
         vaiqueimar:= true;
   2: for k:= 0 to 3 do
      if hand[k] = 0 then
         vaiqueimar:= true;
   3: for k:= 0 to 3 do
      if hand[k] = 0 then
         c3:= c3 + 1;
      if c3 >= 2 then
         vaiqueimar:= true;
   4: for k:= 0 to 3 do
      if hand[k] = 0 then
         c4:= c4 + 1;
      if c4 >= 3 then
         vaiqueimar:= true;
   queima:= vaiqueimar;
end;

procedure passaTempo(var mat: matriz; n, m: integer);
var i, j: integer; 
begin
   for i:= 1 to n do
   begin
      for j:= 1 to m do
      begin
         if (mat[i, j] > 0) AND (mat[i, j] <= 4) then
         begin
            if queima(mat, i, j, n, m) then
            begin
               mat[i, j]:= -1;
            end;
         end;
      end;
   end;
end;

procedure muda(var mat: matriz; n, m: integer);
var i, j: integer; 
begin
   for i:= 1 to n do
   begin
      for j:= 1 to m do
      begin
         if mat[i, j] = -1 then
            mat[i, j]:= 0;
      end;
   end;   
end;

procedure achaZero(var mat: matriz; n, m: integer);
var i, j, cont: integer;
begin
   cont:= 0;
   for i:= 1 to n do
   begin
      for j:= 1 to m do
      begin
         if mat[i, j] = 0 then
            cont:= cont + 1;
      end;
   end;
   writeln(cont);
end;

begin
   read(n, m, t);
   leMat(mat, n, m);
   for k:= 1 to t do
   begin
      passaTempo(mat, n, m);
      muda(mat, n, m);
   end;
   achaZero(mat, n, m);
end.