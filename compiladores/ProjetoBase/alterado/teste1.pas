program testegoto (input, output);
label 1;
var a:  integer;

begin
   a := 10;
   1: a := a-1;
   if(a > 0) then
      goto 1;
end.