program clareia_imagem;
const
    cte = 25;
type
    imagem = array[1..1000, 1..1000] of integer;
var
    O  : imagem;
    p2 : string;
    n  : integer;
    m  : integer;
    max: integer;

procedure leMat( var O: imagem; n,m: integer );
var i, j: integer;

begin
    for i:= 1 to n do 
    begin
        for j:= 1 to m do
            read( O[i, j] );
    end;
end;

procedure clareia( var O: imagem; n, m, max: integer );
var i, j: integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to m do
        begin
            O[i, j]:= O[i, j] + cte;
            if O[i, j] > max then
                O[i, j]:= max;        
        end;
    end;
end;

procedure escImg( var O: imagem; n, m: integer );
var i, j: integer;

begin
    for i:= 1 to n do
    begin
        for j:= 1 to m do
            write( O[i, j], ' ' );
        writeln; 
    end;
end;

begin
    read( p2, n, m, max );
    leMat( O, n, m );
    clareia( O, n, m, max );
    writeln ( 'P2' );
    writeln( n, ' ', m );
    writeln( max );
    escImg( O, n, m );
end.