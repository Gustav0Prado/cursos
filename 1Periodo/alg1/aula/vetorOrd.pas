program vetorOrd;
const
   MIN = 1;
   MAX = 200;

type
   tpVetor = Array[MIN..MAX] of integer;

var
   v	 : tpVetor;
   tam	 : integer;
   num	 : integer;
   rep	 : integer;
   achou : boolean;

procedure escreveVetor(var v : tpVetor; tam : integer);
var
   i : integer;

begin
   for i:= 1 to tam do
      write( v[i], ' ' );
   writeln;
end;

function existe(num : integer; var v : tpVetor; tam : integer; var achou : boolean ) : integer;
var ind	: integer;

begin
   ind:= MIN;
   achou:= false;
   while ( not achou ) AND ( ind <= tam ) do
      begin
	 if v[ind] = num then
	    begin
	       existe:= ind;
	       achou:= true;
	    end;
	 ind:= ind + 1;
      end;
end;
   
		    
procedure ordenaVetor(num : integer;  var v : tpvetor;  var tam : integer);
var i : integer;
   
begin
   i:= tam;
   while ( i >= MIN ) AND ( v[i] > num ) do
      begin
        v[i+1]:= v[i];
        i:= i - 1;
      end;
   v[i + 1]:= num;
   tam:= tam + 1;
end;

procedure removeVet(num	: integer; var v : tpVetor; var tam : integer; rep : integer );
var
   i : integer;

begin
   i:= rep;
   while i < ( tam  ) do
      begin
	 v[i]:= v[i] + 1;
	 i:= i + 1;
      end;
   tam:= tam - 1;
end;
			
begin
   tam:= MIN - 1;
   achou:= false;
   read( num );
   while ( num <> 0 ) AND ( tam < MAX ) do
      begin
        rep:= existe( num, v, tam, achou );
        if achou = false then
            ordenaVetor( num, v, tam )
        else
            begin
                removeVet( num, v, tam, rep );
                ordenaVetor( num, v, tam );
            end;
        read( num );
      end;
   escreveVetor( v, tam );
   write( 'escreva um numero para remover ' );
   read( num );
   while num <> 0 do
      begin
        rep:= existe( num, v, tam, achou );
        removeVet( num, v, tam, rep );
        escreveVetor( v, tam );
        read( num );
      end;
end.
