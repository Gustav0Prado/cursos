program proc2 (input, output);
var x, y: integer;
   procedure p(t:integer; var u :integer);
   begin
      t := t + 10;
      write(t);
      u := u + 10;
   end;
begin
   read(x, y);
   p(x-1, y);
   write(y);
end.