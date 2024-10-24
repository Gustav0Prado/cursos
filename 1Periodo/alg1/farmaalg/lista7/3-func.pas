program func_3;
const MAX =  200;
type
   vet =  Array[1..MAX] of integer;
var
   v   : vet;
   tam : longint;
   
procedure leVetor(tam : longint;  var v: vet);
var ind	: longint;

begin
   ind:= 1;
   while ind <= tam do
      begin
	 read( v[ind] );
	 ind:= ind + 1;
      end;
end;

function crescVetor (tam : longint; v : vet) : boolean;
var ind	: longint; ord : boolean;

begin
   ind:= 1;
   while ind <= tam do
      begin
	 if v[ind] > v[ind - 1] then
	    ord:= true
	 else
	    ord:= false;
	 ind:= ind + 1;
      end;
   crescVetor:= ord;
end;

procedure escreveVetor(tam : longint; v : vet);
var i :  longint;
   
begin
   for i:= tam downto 1 do
      write( v[i], ' ' );
   writeln;
end;
			 
begin
   read( tam );
   if tam = 0 then
      writeln( 'vetor vazio' )
   else
      begin
	 leVetor( tam, v );
	 if crescVetor( tam, v ) then
	    begin
	       writeln( 'sim' );
	       writeln;
	       writeln;
	    end
	 else
	    begin
	       writeln( 'nao' );
	       writeln;
	       writeln;
	    end;
	 escreveVetor( tam, v );
      end;
   
end.
