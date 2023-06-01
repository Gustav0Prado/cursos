program proc2 (input, output);
var x, y: integer;
   procedure p(t, u:integer);
   begin
      t := t + u;
      write(t);
   end;
begin
   read(x, y);
   p(x, y);
   write(x);
end.