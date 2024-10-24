program test;
var num : integer;

begin
	read( num );
	while num <> 0 do
		begin
			if num > 10 then
				writeln( 'Maior que dez' )
			else if num < 10 then
				writeln( 'Menor que dez' );
		end;
end.
