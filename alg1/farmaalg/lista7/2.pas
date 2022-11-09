program vetorOrd;
const
   MIN = 1;
   MAX = 200;

type
   tpVetor = Array[MIN..MAX] of real;

var
   v	 : tpVetor;
   tam	 : integer;
   num	 : real;
   op	 : integer;
   rep	 : integer;
   achou : boolean;

procedure escreveVetor(var v : tpVetor; tam : integer);
var
   i : integer;

begin
   for i:= 1 to tam do
      write( v[i]:0:1, ' ' );
   writeln;
end;

function existe(num : real; var v : tpVetor; tam : integer; var achou : boolean ) : integer;
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
   
		    
procedure ordenaVetor(num : real;  var v : tpvetor;  var tam : integer);
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

procedure removeVet(num	: real; var v : tpVetor; var tam : integer; rep : integer );
var
   i : integer;

begin
   i:= rep;
   while i < ( tam  ) do
      begin
	 v[i]:= v[i + 1];
	 i:= i + 1;
      end;
   tam:= tam - 1;
end;
			
begin
   tam:= MIN - 1;
   achou:= false;
   read( op );
   while ( op <> 0 ) do
      begin
	 if tam = MAX then
	    begin
	       read( num );
	       writeln( 'erro' )
	    end
	 else
	    if op = 1 then
	       begin
		  read( num );
		  ordenaVetor( num, v, tam );
		  escreveVetor( v, tam );
	       end
	 else if op = 2 then
	    begin
	       read( num );
	       rep:= existe( num, v, tam, achou );
	       if not achou then
		  writeln( 'erro' )
	       else
		  begin
		     removeVet( num, v, tam, rep );
		     if tam > 0 then
			escreveVetor( v, tam )
		     else
			writeln( 'vazio' );
		  end;
	    end;
	 read( op );
      end;
   if tam = 0 then
      writeln( 'vazio' )
   else
      escreveVetor( v, tam );	 
end.
