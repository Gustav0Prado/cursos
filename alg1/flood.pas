program floodfill;
uses crt;

const
    MAX = 30; (* dimensao maxima da matriz *)
    GANHOU = 1; (* codigos para o estado atual do jogo *)
    NAO_ACABOU = 2;
    PERDEU = 3;

type 
   tipo_jogo = record
      matriz: array[0..MAX+1, 0..MAX+1] of integer;
      tam, num_jogadas, max_jogadas, num_cores, estado_jogo : integer;
   end;
   pilha = record
      tam: integer;
      fila: array[1..MAX, 1..2] of integer;
   end;
   elemento = record
      x: integer;
      y: integer;
   end;

var jogo: tipo_jogo;

procedure ler_conf_tabuleiro( var jogo: tipo_jogo );
begin
    write ('Num. cores: ') ;
    read ( jogo .num_cores) ;
    write ('tam tabuleiro: ') ;
    read ( jogo .tam) ;
    write ('Max Jogadas: ') ;
    read ( jogo .max_jogadas) ;
end;

procedure iniciar_jogo( var jogo: tipo_jogo );
var i, j: integer;
begin
   randomize;   (* inicia semente randomica *)
   for i:= 1 to jogo.tam do    (* coloca cores aleatorias na matriz *)
   begin
      for j:= 1 to jogo.tam do
         jogo.matriz[i, j]:= random(jogo.num_cores) + 1;   
   end;
   jogo.estado_jogo:= NAO_ACABOU;
   jogo.num_jogadas:= 0;
   for i:= 0 to jogo .tam + 1 do
   begin
      jogo.matriz[0 , i ]:= 0;
      jogo.matriz[ jogo.tam+1,i ]:= 0;
      jogo.matriz[ i ,0]:= 0;
      jogo.matriz[ i , jogo.tam+1]:= 0;
   end;
end;

procedure imprimir_jogo( var jogo: tipo_jogo);
var i, j: integer;
begin
   clrscr;
   writeln( jogo.num_jogadas, '/', jogo.max_jogadas );
   writeln;
   for i:= 1 to jogo.tam do
   begin
      for j:= 1 to jogo.tam do
      begin
         textbackground( jogo.matriz[i, j] );
         write( jogo.matriz[i, j]:3, ' ' );
      end;
      writeln;
   end;
   textbackground( black );
end;

function ganhou_jogo( var jogo: tipo_jogo): boolean;
begin
   ganhou_jogo:= jogo.estado_jogo = GANHOU;
end;

function acabou( var jogo: tipo_jogo ): boolean;
begin
   if jogo.estado_jogo <> NAO_ACABOU then
      acabou:= true
   else
      acabou:= false;
end;

function escolhe_cor( var jogo: tipo_jogo ): integer;
var cor: integer;
begin
   repeat
      read( cor );
   until ( cor >= 1) AND ( cor <= jogo.num_cores );
   escolhe_cor:= cor;
end;

procedure inicializa_pilha( var p: pilha );
begin
   p.tam:= 0;
end;

procedure empilha( e: elemento; var p: pilha );
var tam: integer;
begin
   p.tam:= p.tam + 1;
   tam:= p.tam;
   p.fila[tam, 1]:= e.x;
   p.fila[tam, 2]:= e.y;
end;

function pilha_vazia( var p: pilha ): boolean;
begin
   if p.tam = 0 then
      pilha_vazia:= true
   else
      pilha_vazia:= false;
end;

function desempilha( var p: pilha ): elemento;
var i: integer; res: elemento;
begin
   res.x:= p.fila[1, 1];
   res.y:= p.fila[1, 2];
   for i:= 1 to p.tam - 1 do
   begin
      p.fila[i, 1]:= p.fila[i + 1, 1];
      p.fila[i, 2]:= p.fila[i + 1, 2];
   end;
   p.tam:= p.tam - 1;
   desempilha:= res;
end;

function testa_vitoria( var jogo: tipo_jogo): boolean;
var i, j: integer; ok: boolean;
begin
   ok:= true;
   i:= 1;
   while ( i <= jogo.tam ) and ok do
   begin
      j:= 1;
      while (j <= jogo.tam) and ok do
      begin
         if jogo.matriz[i, j] <> jogo.matriz[1, 1] then
            ok:= false;
         j:= j + 1;
      end;
      i:= i + 1;
   end;
   testa_vitoria:= ok;
end;

function inunda_vizinho( var jogo: tipo_jogo; cor_velha, cor_nova, x, y: integer): boolean;
begin
   inunda_vizinho:= false;
   if jogo.matriz[x, y] = cor_velha then
   begin
      jogo.matriz[x, y]:= cor_nova;
      inunda_vizinho:= true;
   end;
end;

procedure inunda( var jogo: tipo_jogo; cor_nova: integer );
var p: pilha; e: elemento; cor_velha: integer;
begin
   jogo.num_jogadas:= jogo.num_jogadas + 1;
   inicializa_pilha( p );
   e.x:= 1;
   e.y:= 1;
   cor_velha:= jogo.matriz[1, 1];
   jogo.matriz[1, 1]:= cor_nova;
   empilha( e, p );
   while not pilha_vazia( p ) do
   begin
      e:= desempilha(p);
      e.x:= e.x - 1;    (* vizinho de cima *)
      if inunda_vizinho( jogo, cor_velha, cor_nova, e.x, e.y) then
         empilha(e, p);
      e.x:= e.x + 2;    (* vizinho de baixo *)
      if inunda_vizinho( jogo, cor_velha, cor_nova, e.x, e.y) then
         empilha(e, p);
      e.x:= e.x - 1;
      e.y:= e.y - 1;    (* vizinho da esquerda *)
      if inunda_vizinho( jogo, cor_velha, cor_nova, e.x, e.y) then
         empilha(e, p);
      e.y:= e.y + 2;    (* vizinho da direita *)
      if inunda_vizinho( jogo, cor_velha, cor_nova, e.x, e.y) then
         empilha(e, p);
   end;
   if testa_vitoria(jogo) then
      jogo.estado_jogo:= GANHOU
   else if jogo.num_jogadas > jogo.max_jogadas then
      jogo.estado_jogo:= PERDEU;
end;

begin
    ler_conf_tabuleiro( jogo );
    iniciar_jogo( jogo );
    repeat
         imprimir_jogo( jogo );
         inunda( jogo, escolhe_cor(jogo) );
    until ( acabou( jogo ) );
    imprimir_jogo( jogo );
    if ganhou_jogo( jogo ) then
        writeln( 'Parabens voce ganhou' )
    else
        writeln( 'Jogue Novamente' );
end.