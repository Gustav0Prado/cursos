program serie;
var
   x, i	    : integer;
   num, den : longint;

procedure calculaTermo( x, i : integer; var num, den : longint );
var cont, fat : integer;

begin
    den:= 1;                            //comaçea den com o den do primeiro termo (1)
    num:= 1;                            //começa num com o num do primeiro termo  (0!)
    cont:= 0;                           //contador do exponencial
    while cont < ( i - 1 ) * 2 do       //( i - 1 ) * 2  representa o expoente a ser alcançado
    begin
        num:= num * x;                  //multiplica até alcançar expoente
        cont:= cont + 1;
        writeln( num, ' ', cont );
    end;
    if i mod 2 = 0 then                 //termos pares são negativos
        num:= -num;
    for fat:= cont downto 1 do          //fatorial de cont ( cont = igual ao expo ) eh o denomin
        den:= den * fat;
end;

begin
   write( 'Entre com o valor de x e a posição do termo: ' );
   readln( x, i );
   calculaTermo( x, i, num, den );
   writeln( i, '-esimo termo = ', num, '/', den );
end.
