program A;
type
  vet = array[0..10000] of char;

var
  v: vet;
  n: integer;
  
function ehCont( var v: vet; i, n: integer): boolean;
var k: integer; ehseq: boolean;
  seq: vet;

begin
  ehseq:= true;
  seq[0]:= 'C';
  seq[1]:= 'A';
  seq[2]:= 'U';
  seq[3]:= 'A';
  seq[4]:= 'U';
  seq[5]:= 'G';
  seq[6]:= 'A';
  seq[7]:= 'C';
  seq[8]:= 'U';
  for k:=0 to 8 do
    begin
      if v[i + k] <> seq[k] then
        ehseq:= false;
    end;
  ehCont:= ehseq;
end;

procedure leSeq(var v: vet; n:integer);
var i: integer;

begin
  for i:= 0 to n do
    read(v[i]); 
end;

function achaPoli(var v: vet; n:integer): Integer;
var i, cont, contmax:integer;

begin
  cont:= 0;
  contmax:= 0;
  i:= 0;
  while i <= n - 1 do
  begin
    if v[i] = 'A' then
    begin
      cont:= cont + 1;
    end
    else if (v[i] = 'G') AND (cont >= 7) then
    begin
      if ehCont(v, i + 1, n) then
        begin
          i:= i + 9;
          cont:= cont + 10;
        end
    end
    else
    begin
      if cont > contmax then
      contmax:= cont;
        cont:= 0;
    end;
    i:= i + 1;
   end;
  if cont > contmax then
  contmax:= cont;
  if contmax < 7 then
  contmax:= 0;
  achaPoli:= contmax;
end;

begin
  readln(n);
  leSeq(v, n);
  writeln(achaPoli(v, n));
end.