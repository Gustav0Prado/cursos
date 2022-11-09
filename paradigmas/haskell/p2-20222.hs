procura::Int->[Int]->Bool
procura a [] = False
procura a (b:x)
   |(a == b) = True
   |otherwise = procura a x

tem_comuns::[Int]->[Int]->Bool
tem_comuns a [] = False
tem_comuns [] b = False
tem_comuns (a:x) b
   |(procura a b) = True
   |otherwise = tem_comuns x b

fatduplo::Int->Int
fatduplo 0 = 1
fatduplo a
   |(mod a 2 == 1) = a*(fatduplo (a-1))
   |otherwise = fatduplo (a-1)

binario::Int->Int
binario 0 = 0
binario a = 10 * binario (div a 2)+(mod a 2)

fatores::Int->[Int]
fatores n = [x | x <- [1..n], mod n x == 0]

primo::Int->Bool
primo n = (fatores n) == [1,n]

primos::Int->[Int]
primos n = [x | x <- [1..n], primo x]

isPrimo::Int->Bool
isPrimo 1 = False
isPrimo 2 = True
isPrimo n
   |(length [x | x <- [2..n-1], mod n x == 0]) > 0 = False
   |otherwise = True

goldbach::Int->(Int, Int)
goldbach x
   |(x > 2 && mod x 2 == 0) = head [(a,b) | a<- [1..x], b <- [1..x], isPrimo a, isPrimo b, a+b == x]
   |otherwise = (0,0)

mapear::(a->k->b)->[a]->k->[b]
mapear f [] n = []
mapear f (a:x) n = (f a n):mapear f x n

f::Int->Int->Int
f a x = a*x

base x
   |x == 1 = ("joao", "mestre", 'm', 35)
   |x == 2 = ("jonas", "doutor", 'm', 37)
   |x == 3 = ("joice", "mestre", 'f', 30)
   |x == 4 = ("janete", "doutor", 'f', 38)
   |x == 5 = ("jocileide", "doutor", 'f', 50)
   |otherwise = ("ninguem", "", 'n', 0)

genero::(String, String, Char, Int)->Char
genero (a, b, c, d) = c

doutoras::Int->Int
doutoras 6 = 0
doutoras x
   |(genero (base x) == 'f') = 1+(doutoras (x+1))
   |otherwise = doutoras (x+1)