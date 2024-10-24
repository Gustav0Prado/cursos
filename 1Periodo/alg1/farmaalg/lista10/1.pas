program jogo_damas;
const
    MAX = 8;
type
    matriz = array[1..MAX, 1..MAX] of integer;
    vetor = array[1..24] of integer;
var
    mat   : matriz;
    tomar : vetor;
    ficar : vetor;
    mover : vetor;
    tamm  : integer;
    tamf  : integer;
    tamt  : integer;

procedure leMat( var mat: matriz );
var i, j: integer;

begin
    for i:= 1 to MAX do
    begin
        for j:= 1 to MAX do
            read( mat[i, j] );
    end;
end;

procedure esqdir( var mat: matriz; i, j: integer; var tamm, tamt, tamf : integer );
var esq, dir: integer;

begin
    if j = 1 then
        esq:= -1
    else
        esq:= mat[i+1, j-1];
    if j = MAX then
        dir:= -1
    else
        dir:= mat[i+1, j+1];
    if ( ( esq = 0 ) OR ( dir = 0 ) ) and (( esq <> 1 ) AND ( dir <> 1)) then
    begin
        tamm:= tamm + 2;
        mover[tamm - 1]:= i;
        mover[tamm]:= j;
    end
    else if ( esq = -1 ) OR ( dir = -1 ) then
    begin
        tamf:= tamf + 2;
        ficar[tamf - 1]:= i;
        ficar[tamf]:= j;
    end
    else if ( esq = 1 ) OR ( dir = 1 ) then
    begin
        tamt:= tamt + 2;
        tomar[tamt - 1]:= i;
        tomar[tamt]:= j;
    end;
end;

procedure analisa( var mat: matriz; var tomar, ficar, mover: vetor; var tamm, tamf, tamt : integer );
var i, j: integer;

begin
    tamm:= 0;
    tamt:= 0;
    tamf:= 0;
    for i:= 1 to MAX do
    begin
        for j:= 1 to MAX do
        begin
            if mat[i, j] = -1 then
                esqdir( mat, i, j, tamm, tamt, tamf );
        end;
    end;
end;

procedure escVetor( var tomar, mover, ficar: vetor; tamt, tamm, tamf: integer );
var i: integer;

begin

    write( 'tomar: ' );
    if tamt > 0 then
    begin
        i:= 2;
        while i <= tamt do
        begin
            write( tomar[i - 1], '-', tomar[i], ' ' );
            i:= i + 2;
        end;
    end
    else
        write( 0 );
    writeln;
    write( 'mover: ' );
    if tamm > 0 then
    begin
        i:= 2;
        while i <= tamm do
        begin
            write( mover[i - 1], '-', mover[i], ' ' );
            i:= i + 2;
        end;
    end
    else
        write( 0 );
    writeln;
    write( 'ficar: ' );
    if tamf > 0 then
    begin
        i:= 2;
        while i <= tamf do
        begin
            write( ficar[i - 1], '-', ficar[i], ' ' );
            i:= i + 2;
        end;
    end
    else
        write( 0 );
    writeln;
end;


begin
    leMat( mat );
    analisa( mat, tomar, ficar, mover, tamm, tamf, tamt );
    escVetor( tomar, mover, ficar, tamt, tamm, tamf );
end.
