program proc2 (input, output);
var x, y: integer;
   procedure p(t:integer; u:integer);
   begin
      write(t, u);
   end;
begin
   read(x, y);
   p(x, y);
end.