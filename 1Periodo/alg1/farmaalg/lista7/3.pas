program ordenado;
type
   vet =  Array[1..200] of longint;

var
   v   : vet;
   tam : integer;   
   ind : integer;
   i   : integer;
   ord : boolean;

begin   
   ind:= 1;
   read( tam );
   while ind <= tam do
      begin
	 read( v[ind] );
	 if v[ind] > v[ind - 1] then
	    ord:= true
	 else
	    ord:= false;
	 ind:= ind + 1;
      end;
   if tam = 0 then
      writeln( 'vetor vazio' )
   else if ord then
      begin
	 writeln( 'sim' );
	 writeln;
	 writeln;
	 for i:= tam downto 1 do
	    write( v[i], ' ' );
	 writeln;
      end
   else
      begin
	 writeln( 'nao' );
	 writeln;
	 writeln;
	 for i:= tam downto 1 do
	    write( v[i], ' ' );
	 writeln;
      end;   
end.
