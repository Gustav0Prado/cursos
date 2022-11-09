program achar_indice;
type
   vet = Array[1..200] of longint;

var
   v   : vet;
   tam : integer;

function leVetor(var v : vet; var ind : integer) : boolean;
var num: longint;

begin
   ind:= 0;
   read( num );
   if num = 0 then
      leVetor:= false
   else
      begin
	 leVetor:= true;
	 while num <> 0 do
	 begin
	    ind:= ind + 1;
	    v[ind]:= num;	    
	    read( num );
	 end;
      end;
end;

procedure achaInd(v : vet; tam : integer);
var num, i, achind : integer; achou : boolean;

begin
   i:= 1;
   achou:= false;
   read( num );
   while num <> 0 do
      begin
	 while ( not achou ) AND ( i <= tam ) do
	    begin
	       if v[i] = num then
		  begin
		     achind:= i;
		     achou:= true;
		  end;
	       i:= i + 1;
	    end;
	 if achou then
	    writeln( achind )
	 else
	    writeln( '0' );
	 achou:= false;
	 i:= 1;
	 read( num );
      end;
end;
		    
begin
   if leVetor( v, tam ) then
      achaInd( v, tam )
   else
      writeln( 'vetor vazio' );
end.
