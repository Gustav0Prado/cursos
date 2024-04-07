include "alldifferent.mzn";

enum Nacionalidades = { Noruegues, Britanico, Sueco, Dinamarques, Alemao };
enum Cores          = { Vermelho, Verde, Amarelo, Azul, Branco};
enum Pets           = { Cachorro, Passaro, Gato, Cavalo, Peixe};
enum Bebidas        = { Leite, Cha, Cafe, Cerveja, Agua};
enum Hobbies        = { Basquete, Piano, Futebol, Violino, Baseball};

array[1..5] of var Nacionalidades: arrN;
array[1..5] of var Cores:          arrC;
array[1..5] of var Pets:           arrP;
array[1..5] of var Bebidas:        arrB;
array[1..5] of var Hobbies:        arrH;

constraint alldifferent(arrN);
constraint alldifferent(arrC);
constraint alldifferent(arrP);
constraint alldifferent(arrB);
constraint alldifferent(arrH);

constraint arrN[1] = Noruegues;   % Noruegues mora na primeira casa
constraint arrB[3] = Leite;       % Morador da casa do meio bebe leite

constraint exists (i in 1..5) (arrN[i] = Britanico   /\ arrC[i] = Vermelho);
constraint exists (i in 1..5) (arrN[i] = Sueco       /\ arrP[i] = Cachorro);
constraint exists (i in 1..5) (arrN[i] = Dinamarques /\ arrB[i] = Cha);
constraint exists (i in 1..5) (arrN[i] = Alemao      /\ arrH[i] = Futebol);
constraint exists (i in 1..5) (arrC[i] = Verde       /\ arrB[i] = Cafe);
constraint exists (i in 1..5) (arrH[i] = Baseball    /\ arrP[i] = Passaro);
constraint exists (i in 1..5) (arrH[i] = Violino     /\ arrB[i] = Cerveja);
constraint exists (i in 1..5) (arrC[i] = Amarelo     /\ arrH[i] = Piano);
constraint exists (i in 1..4) (arrC[i] = Verde       /\ arrC[i+1] = Branco);
constraint exists (i1 in 1..4, i2 in 2..5) ((arrH[i1] = Basquete   /\ arrP[i1+1] = Gato)
                            \/ (arrH[i2] = Basquete   /\ arrP[i2-1] = Gato));
constraint exists (i1 in 1..4, i2 in 2..5) ((arrP[i1] = Cavalo     /\ arrH[i1+1] = Piano)
                            \/ (arrP[i2] = Cavalo     /\ arrH[i2-1] = Piano));
constraint exists (i1 in 1..4, i2 in 2..5) ((arrN[i1] = Noruegues  /\ arrC[i1+1] = Azul)
                            \/ (arrN[i2] = Noruegues  /\ arrC[i2-1] = Azul));
constraint exists (i1 in 1..4, i2 in 2..5) ((arrH[i1] = Basquete   /\ arrB[i1+1] = Agua)
                            \/ (arrH[i2] = Basquete   /\ arrB[i2-1] = Agua));

solve satisfy;