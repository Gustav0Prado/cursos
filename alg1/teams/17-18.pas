program notas_alunos;
const
   MIN = 1;
   MAX = 200;
type
   vet	   = Array[MIN..MAX] of real;   //array com as notas
   acmedia = Array[MIN..MAX] of real;   //array com as notas acima da media
   abmedia = Array[MIN..MAX] of real;   //array com as notas abaixo da media

var
   v	      : vet;                  //declara variaveis
   ac	      : acmedia;              
   ab	      : abmedia;             
   medianotas : real;
   tam	      : integer;
   indab      : integer;
   indac      : integer;
   ind        : integer;

procedure leNotas(var v	: vet; var ind : integer);  //proced para ler as notas
var num : real;

begin
   ind:= MIN - 1;              //começa o vetor em 0
   read( num );                //le a nota
   while num <> -1 do          //para no -1
      begin
        ind:= ind + 1;        //aumenta tamanho do vetor
        v[ind]:= num;         //registra a nota no vetor
        read( num );          //le prox numero
      end;  
end;

function  media(var v : vet; tam : integer) : real;   //função que retorna a media
var i : integer; soma : real;

begin
   soma:= 0;                             //inicializa soma
   for i:= 1  to tam do                  //de 1 até o tam maximo do vetor
      soma:= soma + v[i];                //soma os valores
   media:= soma/tam;                     //divide pela quantidade de valores
end;

procedure acimaabaixo(tam : integer; medianotas : real; var ac : acmedia; var ab : abmedia; var iac : integer; var iab : integer);  //proced para notas acima/abaixo da media

var ind	: integer; vind : real;

begin
   iac:= MIN - 1;                       //indicador do vet notas acima
   iab:= MIN - 1;                       //indicador do vet notas abaixo
   for ind:= 1 to tam do                //de 1 ate o tam maximo do vetor com todas as notas
      begin
        vind:= v[ind];                //calcula v[ind] apenas uma vez
        if vind >= medianotas then    //se >= a media entra no vet notas acima
            begin
                iac:= iac + 1;          //'tamanho' do vetor aumena em 1
                ac[iac]:= vind;
            end
        else                          //se < que a media entra no vet notas abaixo
            begin
                iab:= iab + 1;          //'tamanho' do vetor aumenta em 1
                ab[iab]:= vind;
            end;
      end;
end;

begin
   leNotas( v, tam );                       //chama proced para ler notas
   medianotas:= media( v, tam );            //retorno da função de media
   writeln( 'media = ', medianotas:0:2);    //imprime media
   acimaabaixo( tam, medianotas, ac, ab, indac, indab );   //chama proced para notas acima/abaixo da media
   write( 'notas acima da media: ' );         //imprime
   for ind:= MIN to indac do                      //de 1 até o numero de notas acima
      write( ac[ind]:0:1, ' ' );              //imprime elementos do vet notas acima
   writeln;
   write( 'notas abaixo da media: ' );
   for ind:= MIN to indab do                     //de 1 até o numero de notas abaixo
      write( ab[ind]:0:1, ' ' );             //imprime elementos do vet notas abaixo
   writeln;
   writeln( 'acima da media: ', indac );       //imprime 'tamanho'do vetor - quantidade de notas acima
   writeln( 'abaixo da media: ', indab );      //imprime 'tamanho' do vetor - quantidade de notas abaixo
end.
