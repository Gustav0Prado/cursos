program divis;
type
   vet = Array[1..200] of real;
var
   v	   : vet;
   tam	   : longint;
   cont	   : longint;
   i	   : integer;
   somapos : real;
   somaneg : real;

begin
   somapos:= 0;
   somaneg:= 0;
   cont:= 1;
   read( tam );
   while cont <= tam do
      begin
	 read( v[cont] );
	 cont:= cont + 1;
      end;
   for i:= 1 to tam do
      begin
	 if ( i mod 2 = 0 ) AND ( v[i] > 0 ) then
	    somapos:= somapos + v[i]
	 else if ( i mod 2 <> 0 ) AND ( v[i] < 0 ) then
	    somaneg:= somaneg + v[i];
      end;
   if ( somaneg = 0 ) AND ( somapos = 0 ) then
      writeln( 'vetor vazio' )
   else if ( somaneg = 0 ) AND ( somapos <> 0 ) then
      writeln( 'divisao por zero' )
   else
      writeln( somapos/somaneg:0:2 );
end.
