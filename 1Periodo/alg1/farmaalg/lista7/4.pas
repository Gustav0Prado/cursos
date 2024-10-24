program seq_cont;

type
   vet = Array[1..100] of longint;
   nos = Array[1..100] of longint;
   qtn = Array[1..100] of longint;
var
   v	: vet;
   nums	: nos;
   tam	: integer;
   tamn	: integer;
   qtd	: qtn;

procedure leNum(var v : vet; tam : integer);
var cont : integer;
   
begin
   for cont:= 1 to tam do
      read( v[cont] );
end;

procedure quaisNum(v : vet; tam : integer; var nums : nos; var tan : integer);
var ind, i, dif : integer;

begin
   for i:= 1 to 100 do
      nums[i]:= -1;
   dif:= 1;
   tan:= 1;
   for ind:= 1 to tam do
      begin
	 for i:= 1 to tan do
	    begin
	       if v[ind] = nums[i] then
		  dif:= dif + 1;
	    end;
	 if dif = 1 then
	    begin
	       nums[i]:= v[ind];
	       tan:= tan + 1;
	    end
	 else
	    dif:= 1;
      end;
   tan:= tan - 1;
   if tan = 1 then
      write( 'a sequencia tem ', tan , ' numero distinto: ' )
   else
      write( 'a sequencia tem ', tan , ' numeros distintos: ' );
   for ind:= 1 to tan do
      write( nums[ind], ' ' );
   writeln;
end;
			  
procedure quantNum(v : vet; tam : integer; nums : nos; tan : integer; var qtd : qtn);
var ind, i : integer;
   
begin
   for ind:= 1 to tam do
      begin
	 for i:= 1 to tan do
	    begin
	       if v[ind] = nums[i] then
		  qtd[i]:= qtd[i] + 1;
	    end;	 
      end;
   for i:= 1 to tan do
      begin
	 if qtd[i] = 1 then
	    write( nums[i], ' ocorre ', qtd[i], ' vez' )
	 else
	    write( nums[i], ' ocorre ', qtd[i], ' vezes' );
	 writeln;
      end;
   writeln;
end;

begin
   read( tam );
   if tam = 0 then
      writeln( 'vetor vazio' )
   else
   begin
	   leNum( v, tam );
	   quaisNum( v, tam, nums, tamn );
	   quantNum( v, tam, nums, tamn, qtd );
   end;
end.
		     
