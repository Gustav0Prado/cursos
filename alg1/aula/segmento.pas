program segmento_a_b;
var num1, num2 : longint;

function encaixa( a, b : longint ) : boolean;
var cont, menor, nummod : integer;

begin
   cont:= 0;
   nummod:= 1;
   menor:= a;
   while menor <> 0 do
      begin
	 cont:= cont + 1;
	 nummod:= nummod * 10;
	 menor:= menor div 10;
      end;
   if a = ( b mod nummod ) then
      encaixa:= true
   else
      encaixa:= false;
end;
		      
function ehSegmento( a, b : longint ) : boolean;
var encaixou : boolean;

begin
   encaixou:= false;
   while encaixou = false AND ( b >= a ) do
      begin
	 encaixou:= encaixa( a, b );
	 b:= b div 10;
      end;
   if encaixou then
      ehSegmento:= true
   else
      ehSegmento:= false;
end;
				 

begin
   writeln( 'Entre com dois inteiros' );
   read( num1, num2 );
   if num1 > num2 then
      begin
	 if ehSegmento( num2, num1 ) then
	    writeln( 'Eh segmento' )
	 else
	    writeln( 'Nao eh segmento' );
      end
   else
      begin
	 if ehSegmento( num1, num2 ) then
	    writeln( 'Eh segmento' )
	 else
	    writeln( 'Nao eh segmento' );
      end;
end.
