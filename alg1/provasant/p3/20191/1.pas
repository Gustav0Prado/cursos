CONST MAX = 100;
TYPE
   elemento = longint;
   pilha = record
      ini: longint;
      v: array [1..MAX] of elemento;
   end;
VAR
   p   : pilha;
   x   : elemento;
   num : elemento;
   ok  : boolean;
   vazio: boolean;

procedure inicializa_pilha( var p: pilha );
begin
   p.ini:= 101;  
end;

procedure empilha( x: elemento; var p: pilha );
begin
   p.ini:= p.ini - 1;
   p.v[p.ini]:= x;
end;

function desempilha( var p: pilha ): elemento;
begin
   desempilha:= p.v[p.ini];
   p.ini:= p.ini + 1;
end;

function pilha_vazia( var p: pilha ): boolean;
begin
   if p.ini = 101 then
      pilha_vazia:= true
   else
      pilha_vazia:= false;
end;

begin
   ok:= true;
   vazio:= false;
   inicializa_pilha( p );
   read( x );
   while x <> 0 do
   begin
      if x > 0 then
         empilha( x, p )
      else
      begin
         num:= desempilha( p );
         if ( - num ) <> x then
            ok:= false;
      end;
      if pilha_vazia( p ) then
         vazio:= true;
      read( x );
   end;
   if ok AND vazio then
      writeln( 'SIM' )
   else
      writeln( 'NAO' );
end.