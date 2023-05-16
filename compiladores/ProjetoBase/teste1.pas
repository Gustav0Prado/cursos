program cmdIf (input, output);
var i : integer;

procedure q;
begin
	i := i + 2;
end;

procedure p;
begin
	i := i + 1;
	q;
end;

begin
	read(i);
	p;
	write(i);
end.
